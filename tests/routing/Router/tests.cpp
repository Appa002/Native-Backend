#define BOOST_TEST_MODULE routing_Router_tests

#include <boost/test/unit_test.hpp>
#include <native-backend/routing/Router.h>
#include <native-backend/server/HttpVerb.h>
#include <native-backend/errors/errors.h>
#include <iostream>

BOOST_AUTO_TEST_SUITE(routing_Router_tests)

    BOOST_AUTO_TEST_CASE( incorrect_route_test ) {
        using namespace native_backend;
        try{
            Router::getInstance()->evalulateRoute(HttpVerb::get, "/i/dont/exist");
        }catch(invalid_route_error e){
            BOOST_ASSERT(true);
            return;
        }
        BOOST_ASSERT(false);
    }

    BOOST_AUTO_TEST_CASE( incorrect_http_verb_test ) {
        using namespace native_backend;
        try{
            Router::getInstance()->addRoute(HttpVerb::get, "/i/exist",
                                            std::function<boost::movelib::unique_ptr<Widget>(void)>([](){
                                                return boost::movelib::unique_ptr<Widget>();
                                            }));

            Router::getInstance()->evalulateRoute(HttpVerb::post, "/i/exist");
        }catch(invalid_route_error e){
            BOOST_ASSERT(true);
            return;
        }
        BOOST_ASSERT(false);
    }

    BOOST_AUTO_TEST_CASE( simple_evalulation_test ) {
        using namespace native_backend;
        bool* pModified = new bool(false);

        try{
            Router::getInstance()->addRoute(HttpVerb::get, "/i/exist",
                                            std::function<boost::movelib::unique_ptr<Widget>(void)>([&](){
                                                *pModified = true;
                                                return boost::movelib::unique_ptr<Widget>();
                                            }));
            Router::getInstance()->evalulateRoute(HttpVerb::get, "/i/exist");
        }catch(std::exception e){
            BOOST_TEST_MESSAGE(e.what());
            BOOST_ASSERT(false);
            return;
        }

        BOOST_ASSERT(pModified);
        delete pModified;
    }

BOOST_AUTO_TEST_SUITE_END()
