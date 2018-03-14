//
// Created by albert on 3/12/18.
//

#ifndef NATIVE_BACKEND_TCPCONNECTION_H
#define NATIVE_BACKEND_TCPCONNECTION_H

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

namespace nvb{

    /*!\brief Class for handling tcp/http traffic.
     * This class actually pareses the request of the client to respond accordingly.*/
    class TcpConnection :
            public boost::enable_shared_from_this<TcpConnection> {
    public:
        typedef boost::shared_ptr<TcpConnection> shared_ptr_t;

        static shared_ptr_t create(boost::asio::io_context& io_context);
        void setRef(shared_ptr_t shared_ptr_to_this);
        void start();
        tcp::socket& getSocket();


    private:
        boost::shared_ptr<TcpConnection> shared_ptr_to_this_;
        boost::asio::streambuf request_buffer_;
        tcp::socket socket_;

        explicit TcpConnection(boost::asio::io_context& io_context);

        void onResponded(const boost::system::error_code &, size_t);
        void onRequestRead(const boost::system::error_code &, size_t);
        std::string createResponse(std::string request);
    };

}
#endif //NATIVE_BACKEND_TCPCONNECTION_H
