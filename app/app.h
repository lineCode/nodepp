#pragma once

#include "node/log.h"
#include "node/io_service_pool.h"
#include "node/tcp_server.h"
#include <string>
#include <memory>

using namespace node;

class app
{
	public:
		explicit app(io_service_pool& pool);
		virtual ~app();

		bool init();
		void stop();


		void on_connect(tcp_connection_ptr);
		void on_msg(tcp_connection_ptr conn, std::string&);
		void on_error(tcp_connection_ptr, const boost::system::error_code& error, const std::string& info);

		std::shared_ptr<tcp_server> server_;
		io_service_pool& pool_;
};
