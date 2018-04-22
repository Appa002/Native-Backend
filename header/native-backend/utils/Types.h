//
// Created by albert on 3/23/18.
//

#ifndef NATIVE_BACKEND_TYPES_H
#define NATIVE_BACKEND_TYPES_H

#include <string>
#include <cstring>

namespace nvb{
    template <class T>
    class UnitValue{
    public:
        T value;
        std::string unit;
        UnitValue(T val, std::string& unit) : value(val), unit(unit) {}
        UnitValue(T val, std::string&& unit) : value(val), unit(unit) {}
    };

    class string_view {
    public:
        constexpr string_view(const char* string) : string(string), length(std::strlen(string)) {}
        constexpr string_view(const char* string, const size_t length) : string(string), length(length) {}

        const char* string;
        const size_t length;

        operator std::string() const { return string; }
    };

}

#endif //NATIVE_BACKEND_TYPES_H
