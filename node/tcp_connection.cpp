#include "tcp_connection.h"
#include "log.h"
#include <iostream>
#include "boost/lexical_cast.hpp"
#include <cstring>

using namespace node;
//using namespace std::placeholders;

tcp_connection::tcp_connection(io_service& io)
	:socket_(io), data_(nullptr) 
{
	reading_ = false;

	id_ = 0;
}

void tcp_connection::handle_error(const boost::system::error_code& error, const std::string& info)
{
	logger::log("%s, %s", __func__, info.c_str());
	close();
}

void tcp_connection::handle_read(const boost::system::error_code& error, size_t bytes)
{
	if (!error) {
		unsigned int msg_len = boost::asio::detail::socket_ops::network_to_host_long(head_length_);
		body_buff_.resize(msg_len);
		boost::asio::async_read(socket_, boost::asio::buffer(&body_buff_[0], body_buff_.size()),
				std::bind(&tcp_connection::handle_read_body, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}
	else
	{
		handle_error(error, "read");
	}
}

void tcp_connection::handle_read_body(const boost::system::error_code& error, size_t bytes)
{
	if (!error && bytes > 0) {
		msgHandler(shared_from_this(), body_buff_);
		async_read();
	}
	else
	{
		handle_error(error, "read");
	}
}

void tcp_connection::handle_write(const boost::system::error_code& error, size_t bytes)
{
	if (!error) {
		auto front = sending_queue_.front();
		assert(front.second == bytes);
		delete [] (const char*)(front.first);
		sending_queue_.pop();

		//keep sending
		if (!sending_queue_.empty())
		{
			auto f = sending_queue_.front();
			boost::asio::async_write(socket_, boost::asio::buffer(f.first, f.second), 
					std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
		}
	}
	else {
		handle_error(error, "write");
	}
}

//add 4 bytes msg length header
//normally run logic thread
void tcp_connection::send_msg(const char*p, const size_t len)
{
	size_t size = len + 4;
	//TODO:use memory pool
	char* buf = new char[size];
	unsigned int ns = boost::asio::detail::socket_ops::host_to_network_long(len);
	unsigned int* plen = reinterpret_cast<unsigned int*>(buf);
	*plen = ns;
	memcpy(buf + 4, p, len);
	get_io_service().post(std::bind(&tcp_connection::send_in_queue, shared_from_this(), buf, size));
}

void tcp_connection::send_in_queue(const char* p, const size_t size) {
	bool sending = !sending_queue_.empty();
	sending_queue_.push(std::make_pair(p, size));
	if (!sending) {
		boost::asio::async_write(socket_, boost::asio::buffer(p, size), 
				std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}
}

void tcp_connection::start() {
	connected_ = true;
	closed_ = false;

	boost::asio::socket_base::keep_alive option1(true);
	socket_.set_option(option1);
	boost::asio::ip::tcp::no_delay option(true);
	socket_.set_option(option);

	if (connectedHandler)
		connectedHandler(shared_from_this());
	async_read();
}

void tcp_connection::async_read() {
	boost::asio::async_read(socket_, boost::asio::buffer((char*)&head_length_, HEAD_LENGTH_SIZE),
			std::bind(&tcp_connection::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

tcp_connection::~tcp_connection() {
	logger::log("connection: destroy, id=%u", id());
}

void tcp_connection::close() {
	closed_ = true;
	socket_.close();
	logger::log("connection close");
}

bool tcp_connection::connect(const std::string& host, const unsigned short port) {
	boost::system::error_code ec;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host.c_str()), port);
	socket_.connect(endpoint, ec);
	if (ec) return false;
	else {
		start();
		return true;
	}
}

void tcp_connection::async_connect(const std::string& host, const unsigned short port) {
	using namespace boost::asio::ip;
	tcp::resolver resolver(get_io_service());
	tcp::resolver::query query(host, boost::lexical_cast<std::string>(port));
	tcp::resolver::iterator iterator = resolver.resolve(query);
	boost::asio::async_connect(socket_, iterator, boost::bind(&tcp_connection::handle_connect, shared_from_this(), boost::asio::placeholders::error));
}

void tcp_connection::handle_connect(const boost::system::error_code& error) {
	if (!error) {
		start();
	}
	else
	{
		handle_error(error, "connect");
	}
}

const std::string tcp_connection::get_remote_ip()
{
	boost::system::error_code ec;
	boost::asio::ip::tcp::socket::endpoint_type endpoint = socket_.remote_endpoint(ec);
	if (ec)
		return "";
	else {
		return endpoint.address().to_string();
	}
}

uint16_t tcp_connection::get_remote_port()
{
	boost::system::error_code ec;
	boost::asio::ip::tcp::socket::endpoint_type endpoint = socket_.remote_endpoint(ec);
	if (ec)
		return 0;
	else {
		return endpoint.port();
	}

}
