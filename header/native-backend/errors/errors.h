//
// Created by albert on 3/13/18.
//

#ifndef NATIVE_BACKEND_INVALID_ROUTE_ERROR_H
#define NATIVE_BACKEND_INVALID_ROUTE_ERROR_H

#include <stdexcept>
#include <native-backend/errors/HttpStatusCode.h>
#include <string_view>
#include <utility>

namespace nvb {
    /*!brief Exception which holds extra information about the http status.*/
    class GeneralError : public std::exception {
    protected:
        const std::string message;
        const nvb::StatusLiteral statusLiteral;
    public:
        GeneralError() = delete;

        explicit GeneralError (char const *const message, nvb::StatusLiteral statusLiteral = nvb::HttpStatusCode::status500) throw()
                            : message(std::string(message)), statusLiteral(std::move(statusLiteral)) {}

        explicit GeneralError (std::string& message, nvb::StatusLiteral statusLiteral = nvb::HttpStatusCode::status500) throw()
                            : message(std::string(message)), statusLiteral(std::move(statusLiteral))  {}

        explicit GeneralError (std::string&& message, nvb::StatusLiteral statusLiteral = nvb::HttpStatusCode::status500) throw()
                            : message(std::string(message)), statusLiteral(std::move(statusLiteral))  {}

        char const *what() const throw() override { return message.c_str(); }

        /*!\brief Return the code associated with the http status.
         * eg. 404 or 200 is returned.*/
        unsigned int statusCode() { return statusLiteral.code; }

        /*!\brief Return the text associated with the http status.
         * eg. For 404 "Not found" would be returned,
         * for 200 "OK" would be returned.*/
        std::string statusText() { return std::string(statusLiteral.text); }

        /*!\brief Returns a instance of \c nvb::StatusWrapper which holds information about the http status.
         * eg. if the status is 200 OK \c StatusWrapper::code would equal 200 and \c StatusWrapper::text
         * would equal "OK".*/
        nvb::StatusWrapper status() { return nvb::StatusWrapper(statusCode(), statusText()); }
    };
}


/*!\brief Macro Used to quickly add custom exceptions.*/
#define ADD_ERROR(name) class name : public nvb::GeneralError { \
public:\
                explicit name (char const *const message, nvb::StatusLiteral statusLiteral = nvb::HttpStatusCode::status500) throw() \
                            : GeneralError(message, statusLiteral) {} \
\
                explicit name (std::string& message, nvb::StatusLiteral statusLiteral = nvb::HttpStatusCode::status500) throw() \
                            :  GeneralError(message, statusLiteral) {} \
\
                explicit name (std::string&& message, nvb::StatusLiteral statusLiteral = nvb::HttpStatusCode::status500) throw() \
                            : GeneralError(message, statusLiteral) {} \
};


namespace nvb::error {
    ADD_ERROR(invalid_route_error)
    ADD_ERROR(no_child_error)
    ADD_ERROR(old_state_error)
    ADD_ERROR(invalid_argument_error)
    ADD_ERROR(invalid_request_error)
}


#endif //NATIVE_BACKEND_INVALID_ROUTE_ERROR_H
