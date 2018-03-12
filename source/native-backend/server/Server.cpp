//
// Created by albert on 3/10/18.
//

#include <iostream>
#include <iterator>
#include "native-backend/server/Server.h"

native_backend::Server::Server(unsigned short port, boost::asio::io_context& io_context) :
        acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {
    start_accept();
}

void native_backend::Server::start_accept() {
    TcpConnection::shared_ptr_t new_connection =
            TcpConnection::create(acceptor.get_executor().context());

    acceptor.async_accept(new_connection->getSocket(),
                           boost::bind(&Server::handle_accept, this, new_connection,
                                       boost::asio::placeholders::error));
}

void native_backend::Server::handle_accept(TcpConnection::shared_ptr_t new_connection,
                                           const boost::system::error_code& error) {

    if(!error){
        new_connection->start();
    }

    start_accept();

}


