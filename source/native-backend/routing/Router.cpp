//
// Created by albert on 3/13/18.
//

#include "native-backend/routing/Router.h"
#include <native-backend/errors/errors.h>
#include <native-backend/errors/HttpStatusCode.h>

/*!\brief Adds a route by mapping a std function to a html verb and path.
 * The mapping is stored in \c Router::routes_map_.*/
void nvb::Router::addRoute(nvb::HttpVerb::Verb verb, std::string path,
                                      std::function<boost::shared_ptr<nvb::IWidget>()> builder) {
    routes_map_[path][verb] = builder;
}

/*!\brief Finds function registered for path / http verb combi and returns it's return value.
 * Throws native_backend::invalid_route_error when the route doesn't exist.*/
boost::shared_ptr<nvb::IWidget>
nvb::Router::evaluateRoute(nvb::HttpVerb::Verb verb, std::string path) {
    if(routes_map_.find(path) == routes_map_.cend())
        throw error::invalid_route_error("No route defined for path: \""+path+"\" with http verb: \""+HttpVerb::toString(verb)+"\"", HttpStatusCode::status404);

    else if (routes_map_.at(path).find(verb) == routes_map_.at(path).end())
        throw error::invalid_route_error("Invalid http verb \""+HttpVerb::toString(verb)+"\" used for route with path: \"" +path+ "\"", HttpStatusCode::status404);

    return routes_map_.at(path).at(verb)();
}
