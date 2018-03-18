//
// Created by albert on 3/13/18.
//

#ifndef NATIVE_BACKEND_INVALID_ROUTE_ERROR_H
#define NATIVE_BACKEND_INVALID_ROUTE_ERROR_H

#include <stdexcept>
#include <native-backend/errors/HttpStatusCode.h>
#include <string_view>

/*!\brief Macro Used to quickly add custom exception which hold extra information about the http status.
 * Defines function \c ::statusCode() and \c statusText() which return the number associated with the http status
 * and return the text associated whith the http status respectively.*/

#define ADD_ERROR(name) class name : public std::exception { \
\
    private: \
        const std::string message; \
        const nvb::StatusLiteral statusLiteral;  \
    public: \
        name (char const* const message, nvb::StatusLiteral statusLiteral = nvb::HttpStatusCode::status500) throw() : message(std::string(message)), statusLiteral(statusLiteral) {}; \
        name (std::string message, nvb::StatusLiteral statusLiteral = nvb::HttpStatusCode::status500) throw() : message(message), statusLiteral(statusLiteral) {} \
        virtual char const* what() const throw(){ return message.c_str(); }; \
        unsigned int statusCode(){ return statusLiteral.code; }\
        std::string statusText(){ return std::string(statusLiteral.text); }\
        nvb::StatusWrapper status() {return nvb::StatusWrapper(statusCode(), statusText()); } \
};


namespace nvb {
    ADD_ERROR(invalid_route_error)
}


#endif //NATIVE_BACKEND_INVALID_ROUTE_ERROR_H
