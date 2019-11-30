#pragma once

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "io_service_pool.h"
#include "tcp_connection.h"
#include <string>
#include <memory>

using boost::asio::ip::tcp;

namespace node
{
	class tcp_server
	{
		public:
			tcp_server(io_service_pool& pool, const std::string& address, const std::string& port)
				: service_pool_(pool), acceptor_(service_pool_.get_io_service())
			{
				// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
				boost::asio::ip::tcp::resolver resolver(acceptor_.get_io_service());
				boost::asio::ip::tcp::resolver::query query(address, port);
				boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

				acceptor_.open(endpoint.protocol());
				acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
				acceptor_.bind(endpoint);
				acceptor_.listen();
			}

			void start_accept()
			{
				tcp_connection_ptr new_connection(new tcp_connection(service_pool_.get_io_service()));

				new_connection->msgHandler = msgHandler;
				new_connection->connectedHandler = connectedHandler;
				new_connection->errorHandler = errorHandler ;

				acceptor_.async_accept(new_connection->socket(),
						boost::bind(&tcp_server::handle_accept, this, new_connection,
							boost::asio::placeholders::error));
			}

		private:
			void handle_accept(tcp_connection_ptr new_connection, const boost::system::error_code& error)
			{
				if (!error)
				{
					new_connection->start();
				}
				start_accept();
			}

			io_service_pool& service_pool_;
			tcp::acceptor acceptor_;

		public:
			std::function<void (tcp_connection_ptr, std::string&)> msgHandler;
			std::function<void (tcp_connection_ptr)> connectedHandler;
			std::function<void (tcp_connection_ptr, const boost::system::error_code& error, const std::string&)> errorHandler;
	};
}
