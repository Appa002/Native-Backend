//
// Created by albert on 3/13/18.
//

#include "native-backend/routing/Router.h"
#include <native-backend/errors/errors.h>

/*!\brief Adds a route by mapping a std function to a html verb and path.
 * The mapping is stored in \c Router::routes_map_.*/
void native_backend::Router::addRoute(native_backend::HttpVerb verb, std::string path,
                                      std::function<boost::movelib::unique_ptr<native_backend::Widget>()> builder) {
    routes_map_[path][verb] = builder;
}

/*!\brief Finds function registered for path / http verb combi and returns it's return value.
 * Throws native_backend::invalid_route_error when the route doesn't exist.*/
boost::movelib::unique_ptr<native_backend::Widget>
native_backend::Router::evalulateRoute(native_backend::HttpVerb verb, std::string path) {
    if(routes_map_.find(path) == routes_map_.cend())
        throw invalid_route_error("No route defined for path: \""+path+"\" with http verb: \""+toString(verb)+"\" ");

    else if (routes_map_.at(path).find(verb) == routes_map_.at(path).end())
        throw invalid_route_error("Invalid http verb \""+toString(verb)+"\" used for route with path: \"" +path+ "\"");

    return routes_map_.at(path).at(verb)();
}
