//
// Created by albert on 3/18/18.
//

#ifndef NATIVE_BACKEND_HTTPSTATUSCODE_H
#define NATIVE_BACKEND_HTTPSTATUSCODE_H

#include <string>
#include <string_view>
#include <utility>

namespace nvb{

    class StatusLiteral{
    public:
        constexpr StatusLiteral(unsigned int code, std::string_view str) : code(code), text(str) {}
        const unsigned int code;
        const std::string_view text;
    };

    class StatusWrapper{
    private:
        unsigned int code;
        std::string text;
    public:
        StatusWrapper(StatusLiteral literal) : code(literal.code), text(std::string(literal.text)) {}
        explicit StatusWrapper(unsigned int code, std::string& str) : code(code), text(std::move(str)) {}
        explicit StatusWrapper(unsigned int code, std::string&& str) : code(code), text(std::move(str)) {}

        unsigned int getCode() { return code; }
        std::string getText() { return text; }

    };

    class HttpStatusCode {
    public:
        static constexpr StatusLiteral status200 = [](){ return StatusLiteral(200, "OK");}();
        static constexpr StatusLiteral status404 = [](){ return StatusLiteral(404, "Not Found");}();
        static constexpr StatusLiteral status500 = [](){ return StatusLiteral(500, "Internal Server Error");}();

    };
}



#endif //NATIVE_BACKEND_HTTPSTATUSCODE_H
