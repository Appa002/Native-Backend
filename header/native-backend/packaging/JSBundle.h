//
// Created by a_mod on 24.04.2018.
//

#ifndef NATIVE_BACKEND_JSBUNDLE_H
#define NATIVE_BACKEND_JSBUNDLE_H

#include <string>

namespace nvb{
    class JSBundle {
    public:
        const std::string passersId;

        JSBundle() : passersId(""){}
        explicit JSBundle(std::string id) : passersId(id) {};
    };
}



#endif //NATIVE_BACKEND_JSBUNDLE_H
