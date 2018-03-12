//
// Created by albert on 3/12/18.
//

#include "native-backend/server/TcpConnection.h"

void native_backend::TcpConnection::start() {
    boost::asio::async_read_until(socket_, this->request_buffer, "\r\n\r\n",
                                  boost::bind(&TcpConnection::onRequestRead, this,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
}

native_backend::TcpConnection::shared_ptr_t native_backend::TcpConnection::create(boost::asio::io_context &io_context) {
    shared_ptr_t myPtr = shared_ptr_t(new TcpConnection(io_context));
    myPtr->setRef(myPtr);
    return myPtr;
}

void native_backend::TcpConnection::setRef(native_backend::TcpConnection::shared_ptr_t shared_ptr_to_this) {
    this->shared_ptr_to_this = shared_ptr_to_this;
}

tcp::socket &native_backend::TcpConnection::getSocket() {
    return this->socket_;
}

native_backend::TcpConnection::TcpConnection(boost::asio::io_context &io_context)
        : socket_(io_context) {}

void native_backend::TcpConnection::onResponded(const boost::system::error_code &, size_t) {
    shared_ptr_to_this.reset();
}

void native_backend::TcpConnection::onRequestRead(const boost::system::error_code &, size_t) {
    std::string request((std::istreambuf_iterator<char>(&this->request_buffer)),
                  std::istreambuf_iterator<char>());

    std::string html = "<html><body><p>" + request + "</p></body></html>";

    std::string message = "HTTP/1.1 200 OK\n"
                                  "Content-length: " + std::to_string(html.size()) + "\n"
                                  "Content-Type: text/html\n\n" +
                          html + "\n";


    boost::asio::async_write(socket_, boost::asio::buffer(message),
                             boost::bind(&TcpConnection::onResponded, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));

}
