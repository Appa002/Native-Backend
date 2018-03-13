//
// Created by albert on 3/13/18.
//

#ifndef NATIVE_BACKEND_UTILS_H
#define NATIVE_BACKEND_UTILS_H

#include <string>

namespace native_backend{
    /*!\brief Most generic toString() function, use specialisation to achieve correct behavior.
     * For example see /header/native-backend/server/HttpVerb.h*/
    template <class T>
    std::string toString(T obj){ return std::string(obj); }
}

#endif //NATIVE_BACKEND_UTILS_H
