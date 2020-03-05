#include "app.h"
#include "boost/lexical_cast.hpp"
#include <iostream>
#include <functional>

using namespace node;
using namespace std;

bool app::init() {
	server_.reset(new tcp_server(pool_, "0.0.0.0", boost::lexical_cast<std::string>(8080)));
	server_->msgHandler = std::bind(&app::on_msg, this, std::placeholders::_1, std::placeholders::_2);
	server_->connectedHandler = std::bind(&app::on_connect, this, std::placeholders::_1);
	server_->errorHandler = std::bind(&app::on_error, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	server_->start_accept();
	return true;
}

app::app(io_service_pool& pool):
	pool_(pool)
{
}

void app::stop()
{
	pool_.stop();
}

app::~app() 
{
	server_.reset();
}

void app::on_connect(tcp_connection_ptr) {
	logger::log("%s", __func__);
}

void app::on_msg(tcp_connection_ptr conn, std::string& msg) {
	//logger::log("%s", __func__);
	//cout<<*msg<<endl;
	conn->send_msg(msg.data(), msg.size());
}

void app::on_error(tcp_connection_ptr, const boost::system::error_code& error, const std::string& info) {
	logger::log("%s", __func__);
}
