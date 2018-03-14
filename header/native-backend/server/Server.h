//
// Created by albert on 3/10/18.
//

#ifndef NATIVE_BACKEND_SERVER_H
#define NATIVE_BACKEND_SERVER_H

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/move/unique_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <native-backend/server/TcpConnection.h>

using boost::asio::ip::tcp;

namespace nvb {
    /*!\brief Class which listens for incoming tcp/http traffic.
     * Does not handle parsing or responding to requests.*/

    class Server {
    private:
        tcp::acceptor acceptor;

        explicit Server(unsigned short port, boost::asio::io_context& io_context);
        void start_accept();
        void handle_accept(TcpConnection::shared_ptr_t new_connection,
                           const boost::system::error_code& error);

    public:
        static boost::movelib::unique_ptr<Server> create(unsigned short port);
    };
}


#endif //NATIVE_BACKEND_SERVER_H
