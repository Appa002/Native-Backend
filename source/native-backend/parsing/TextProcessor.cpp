//
// Created by albert on 3/17/18.
//

#include "native-backend/parsing/TextProcessor.h"

/*!\brief Finds the value specified as key in \c replacement_map in the \c input_string and replaces it with the value for the key.*/
void
nvb::TextProcessor::process(std::string *input_string, std::unordered_map<std::string, std::string> &replacement_map) {
    for(auto replacement_pair : replacement_map){
        while(input_string->find(replacement_pair.first, 0) != input_string->npos){
            size_t position = input_string->find(replacement_pair.first, 0);
            *input_string = input_string->erase(position, replacement_pair.first.size());
            *input_string = input_string->insert(position, replacement_pair.second);
        }
    }
}
