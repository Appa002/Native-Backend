//
// Created by albert on 3/13/18.
//

#ifndef NATIVE_BACKEND_HTTPVERB_H
#define NATIVE_BACKEND_HTTPVERB_H

namespace nvb{
    class HttpVerb{
    public:
        enum class Verb{
            get,
            post
        };

        static std::string toString(HttpVerb::Verb verb){
            switch (verb){
                case (Verb::get):
                    return "GET";
                case (Verb::post):
                    return "POST";
            }
        }

        static HttpVerb::Verb stringToHttpVerb(std::string& verb){
            if(verb == "GET")
                return Verb::get;
            if(verb == "POST")
                return Verb::post;
        }

    };

}


#endif //NATIVE_BACKEND_HTTPVERB_H
