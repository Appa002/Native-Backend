//
// Created by albert on 3/17/18.
//

#ifndef NATIVE_BACKEND_TEXTPROCESSOR_H
#define NATIVE_BACKEND_TEXTPROCESSOR_H

#include <string>
#include <unordered_map>

namespace nvb{
    /*!\brief Functions to provide clean string edits, mainly used by Widgets.*/
    class TextProcessor {
    public:
        static void process(std::string *input_string,
                            std::unordered_map<std::string, std::string> &replacement_map);
    };
}



#endif //NATIVE_BACKEND_TEXTPROCESSOR_H
