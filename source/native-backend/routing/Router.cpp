//
// Created by albert on 3/13/18.
//

#include "native-backend/routing/Router.h"
#include <native-backend/errors/errors.h>
#include <native-backend/errors/HttpStatusCode.h>
#include <boost/shared_ptr.hpp>

/*!\brief Adds a route by mapping a std function to a html verb and path.
 * The mapping is stored in \c Router::routes_map_.*/
void nvb::Router::addRoute(nvb::HttpVerb::Verb verb, std::string path,
                                      std::function<boost::shared_ptr<nvb::IWidget>(boost::shared_ptr<nvb::RequestInformation>)> builder) {
    routes_map_[path][verb] = builder;
}

/*!\brief Finds function registered for path / http verb combi and returns it's return value.
 * Throws native_backend::invalid_route_error when the route doesn't exist.*/
boost::shared_ptr<nvb::IWidget>
nvb::Router::evaluateRoute(boost::shared_ptr<nvb::RequestInformation> requestInformation) {
    if(routes_map_.find(requestInformation->path) == routes_map_.cend())
        throw error::invalid_route_error("No route defined for path: \""+requestInformation->path+"\" with http verb: \""+HttpVerb::toString(requestInformation->http_verb)+"\"", HttpStatusCode::status404);

    else if (routes_map_.at(requestInformation->path).find(requestInformation->http_verb) == routes_map_.at(requestInformation->path).end())
        throw error::invalid_route_error("Invalid http verb \""+HttpVerb::toString(requestInformation->http_verb)+"\" used for route with path: \"" +requestInformation->path+ "\"", HttpStatusCode::status404);

    return routes_map_.at(requestInformation->path).at(requestInformation->http_verb)(requestInformation);
}
