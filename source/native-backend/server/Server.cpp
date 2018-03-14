//
// Created by albert on 3/10/18.
//

#include <iostream>
#include <iterator>
#include "native-backend/server/Server.h"

nvb::Server::Server(unsigned short port, boost::asio::io_context& io_context) :
        acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {
    start_accept();
}

/*!\brief Sets up all objects to receive incoming http/tcp traffic.
 * Creates a instance of TcpConnection which will handle requests.
 * Binds the Server::handle_accept function to be called when a client connects.*/
void nvb::Server::start_accept() {
    TcpConnection::shared_ptr_t new_connection =
            TcpConnection::create(acceptor.get_executor().context());

    acceptor.async_accept(new_connection->getSocket(),
                           boost::bind(&Server::handle_accept, this, new_connection,
                                       boost::asio::placeholders::error));
}

/*!\breif Tells the TcpConnection object to handle the incoming request.
 * Called by Server::start_accept when a new client connects.
 * It also calls start_accept to make it listen for new clients.*/
void nvb::Server::handle_accept(TcpConnection::shared_ptr_t new_connection,
                                           const boost::system::error_code& error) {
    if(!error){
        new_connection->start();
    }
    start_accept();
}

/*!\brief Creates a new server and makes it listen.
 * Returns that sever as a boost unique_ptr*/
boost::movelib::unique_ptr<nvb::Server> nvb::Server::create(unsigned short port) {
    boost::asio::io_context io_context;
    boost::movelib::unique_ptr<Server> server (new Server(port, io_context));
    io_context.run();
    return server;
}
