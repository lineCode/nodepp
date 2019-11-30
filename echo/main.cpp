#include <iostream>

#include "node/tcp_connection.h"
#include "boost/asio.hpp"
#include <thread>
#include "boost/bind.hpp"

using namespace node;

using namespace std;
using namespace boost;

void on_msg(tcp_connection_ptr conn, std::string& msg)
{
	//cout<<"recv: "<<*msg<<endl;
	conn->send_msg(msg.data(), msg.size());
}

int main() {
	asio::io_service io;

	node::tcp_connection_ptr conn(new node::tcp_connection(io));
	conn->msgHandler = std::bind(on_msg, std::placeholders::_1, std::placeholders::_2);
	conn->connect("127.0.0.1", 8080);

	string msg(16000, 'a');
	conn->send_msg(msg.data(), msg.size());

	io.run();
	return 0;
}
