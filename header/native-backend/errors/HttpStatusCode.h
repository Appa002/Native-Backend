//
// Created by albert on 3/18/18.
//

#ifndef NATIVE_BACKEND_HTTPSTATUSCODE_H
#define NATIVE_BACKEND_HTTPSTATUSCODE_H

#include <string>
#include <utility>
#include <native-backend/utils/Types.h>
#include <string_view>

namespace nvb{
    /*!\brief Literal Type which holds basic information about a status.
     * Holds the status code as \c unsigned int and the text that goes with it as \c std::string_view
     * std::string_view is used because std::string has a none trivial deconstructor.*/
    class StatusLiteral{
    public:
		constexpr StatusLiteral(unsigned int code, string_view str) : code(code), text(str) {}
        const unsigned int code;
        const string_view text;
    };

    /*!\brief Class which holds the same information as \c StatusLiteral but isn't a literal type.
     * This is supposed to be used for storing http status codes as it defines thing like the assignment operator
     * or -in general- does not need to comply with the requirements for it to be a literal type.*/
    class StatusWrapper{
    private:
        unsigned int code;
        std::string text;
    public:
        StatusWrapper(StatusLiteral literal) : code(literal.code), text(std::string(literal.text.string)) {}
        explicit StatusWrapper(unsigned int code, std::string& str) : code(code), text(std::move(str)) {}
        explicit StatusWrapper(unsigned int code, std::string&& str) : code(code), text(std::move(str)) {}

        unsigned int getCode() { return code; }
        std::string getText() { return text; }

    };

    /*!\brief Class which holds a list of http status codes as \c static \c constexpr fields of type \c StatusLiteral .
     * Use case: One wants the status code 200; Code: \c HttpStatusCode::status200 would ""return"" a \c StatusLiteral
     * which holds the information \c StatusLiteral::code=200 and \c StatusLiteral::text="OK". */
    class HttpStatusCode {
    public:
        static constexpr StatusLiteral status200 = StatusLiteral(200, "OK");
        static constexpr StatusLiteral status404 = StatusLiteral(404, "Not Found");
        static constexpr StatusLiteral status500 = StatusLiteral(500, "Internal Server Error");

    };
}



#endif //NATIVE_BACKEND_HTTPSTATUSCODE_H
