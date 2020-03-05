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

	std::thread t(boost::bind(&boost::asio::io_service::run, &io));
	while(true) {
		string in;
		cin>>in;
		if (in.empty() || in == "q" || in == "exit") {
			break;
		}
		in.assign(8000,'a');
		//cout<<in<<",size="<<in.size()<<endl;
		conn->send_msg(in.data(), in.size());
	}

	t.join();

	return 0;
}
