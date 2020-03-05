#pragma once

#include "boost/bind.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/asio.hpp"

#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <utility>

namespace node {
	using namespace boost::asio;

	using boost::asio::ip::tcp;

	class tcp_connection;
	typedef std::shared_ptr<tcp_connection> tcp_connection_ptr;

	class tcp_connection: public std::enable_shared_from_this<tcp_connection>
	{
	public:
		static const int HEAD_LENGTH_SIZE = 4;
		static const int READ_BUFF_LENGTH = 4096;
		tcp_connection(io_service& io);
		virtual ~tcp_connection(); 		

		void start();
		void close();
		void async_read();
		void async_read_body();
		void send_msg(const char*p, const size_t len);

		bool connect(const std::string& host, const unsigned short port);
		void async_connect(const std::string& host, const unsigned short port);

		int id() const { return id_; }
		tcp::socket& socket() { return socket_; }
		io_service& get_io_service() { return socket_.get_io_service(); }

		const std::string get_remote_ip();
		uint16_t get_remote_port();

		//callback handler
		std::function<void (tcp_connection_ptr)> connectedHandler;
		std::function<void (tcp_connection_ptr, std::string&)> msgHandler;
		std::function<void (tcp_connection_ptr, const boost::system::error_code& error, const std::string& hint)> errorHandler;
	private:
		void handle_read(const boost::system::error_code& error, size_t bytes);
		void handle_read_body(const boost::system::error_code& error, size_t bytes);

		void handle_write(const boost::system::error_code& error, size_t bytes);
		void handle_error(const boost::system::error_code& error, const std::string& info);
		void handle_connect(const boost::system::error_code& error);

		void send_in_queue(const char* p, size_t n);

		tcp::socket socket_;

		int id_;
		bool reading_;

		bool connected_;
		bool closed_;

		unsigned int head_length_;
		//std::vector<char> received_buff_;
		//char buff_[READ_BUFF_LENGTH];
		std::string body_buff_;
		void* data_;

		std::queue<std::pair<const char*, size_t> > sending_queue_;
	};
};
