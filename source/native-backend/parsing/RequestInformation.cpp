//
// Created by albert on 3/14/18.
//

#include "native-backend/parsing/RequestInformation.h"
#include <boost/regex.hpp>
#include <string>

/*!\brief Extracts the requested path and parameters out of a request string and creates a \c RequestInformation shared pointer with this information.*/
boost::shared_ptr<nvb::RequestInformation> nvb::RequestInformation::create(std::string &requestString) {
    requestString = requestString.substr(0, requestString.find("\n"));
    requestString = requestString.replace(requestString.size() - 1, 1, "");

    std::string verbString = requestString.substr(0, requestString.find(" "));
    HttpVerb::Verb verb = HttpVerb::stringToHttpVerb(verbString);

    requestString = boost::regex_replace(requestString, boost::regex("GET\\ "), "");
    requestString = boost::regex_replace(requestString, boost::regex(".HTTP.*"), "");

    std::string path = boost::regex_replace(requestString, boost::regex("\\?.+"), "");
    std::string paramsString = boost::regex_replace(requestString, boost::regex(".+?(?=\\?)"), "");

    std::unordered_map<std::string, std::string> params;
    size_t idx = 0;

    if(paramsString[0] == '?'){
        while(true){
            if(paramsString.find_first_of('&') == paramsString.npos){
                std::string parameter = paramsString.replace(0, 1, "");
                std::string key = parameter.substr(0, parameter.find_first_of('='));
                std::string value = parameter.substr(parameter.find_first_of('='), parameter.size());
                value = value.replace(0, 1, "");
                params[key] = value;
                break;
            }

            std::string parameter = paramsString.substr(idx, paramsString.find('&', idx));
            if(parameter[0] == '?')
                parameter = parameter.replace(0, 1, "");

            std::string key = parameter.substr(0, parameter.find_first_of('='));
            std::string value = parameter.substr(parameter.find_first_of('='), parameter.size());
            value = value.replace(0, 1, "");

            params[key] = value;
            idx = paramsString.find('&', idx);
            if(idx == paramsString.npos)
                break;
            idx++;
        }
    }


    return boost::shared_ptr<RequestInformation>(new RequestInformation(path, params, verb));
}

/*!\brief Sets the constant members \c path and \c params*/
nvb::RequestInformation::RequestInformation(std::string &path_, std::unordered_map<std::string, std::string> &params_,
                                            nvb::HttpVerb::Verb &verb_) : path(path_), params(params_), http_verb(verb_) {}
