//
// Created by albert on 3/13/18.
//

#ifndef NATIVE_BACKEND_HTTPVERB_H
#define NATIVE_BACKEND_HTTPVERB_H

#include <native-backend/utils/utils.h>

namespace native_backend{
    enum class HttpVerb{
        get,
        post
    };

    template <>
    std::string toString(HttpVerb obj){
        switch (obj){
            case HttpVerb::get:
                return "GET";
            case HttpVerb::post:
                return "POST";
        }
    }

}


#endif //NATIVE_BACKEND_HTTPVERB_H
