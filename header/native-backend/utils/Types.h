//
// Created by albert on 3/23/18.
//

#ifndef NATIVE_BACKEND_TYPES_H
#define NATIVE_BACKEND_TYPES_H

#include <string>

namespace nvb{
    template <class T>
    class UnitValue{
    public:
        T value;
        std::string unit;
        UnitValue(T val, std::string& unit) : value(val), unit(unit) {}
        UnitValue(T val, std::string&& unit) : value(val), unit(unit) {}
    };
}

#endif //NATIVE_BACKEND_TYPES_H
