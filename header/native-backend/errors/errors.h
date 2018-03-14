//
// Created by albert on 3/13/18.
//

#ifndef NATIVE_BACKEND_INVALID_ROUTE_ERROR_H
#define NATIVE_BACKEND_INVALID_ROUTE_ERROR_H

#include <stdexcept>

#define ADD_ERROR(name) class name : public std::exception { \
\
    private: \
        std::string message; \
    public: \
        name (char const* const message) throw() : message(std::string(message)) {}; \
        name (std::string message) throw() : message(message) {} \
        virtual char const* what() const throw(){ return message.c_str(); }; \
};


namespace nvb {
    ADD_ERROR(invalid_route_error)
}


#endif //NATIVE_BACKEND_INVALID_ROUTE_ERROR_H
