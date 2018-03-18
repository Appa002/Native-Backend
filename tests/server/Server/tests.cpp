#define BOOST_TEST_MODULE server_Server_tests

#include <boost/test/unit_test.hpp>
#include <native-backend/server/Server.h>
#include <boost/array.hpp>
#include <boost/thread/thread.hpp>
#include <native-backend/routing/Router.h>
#include <native-backend/widgets/IWidget.h>
#include <boost/move/unique_ptr.hpp>
#include <native-backend/widgets/TextWidget.h>
#include <native-backend/widgets/BlockWidget.h>
#include <native-backend/errors/HttpStatusCode.h>

using boost::asio::ip::tcp;

BOOST_AUTO_TEST_SUITE(server_Server_tests)

    BOOST_AUTO_TEST_CASE(server_existents_check) {

        nvb::Router::getInstance()->addRoute(nvb::HttpVerb::Verb::get, "/", [](){
            return boost::movelib::unique_ptr<nvb::IWidget>(
                    new nvb::BlockWidget(
                            new nvb::TextWidget("Hello, World!")
                          //  new nvb::BlockWidgetStyle(nvb::BlockWidgetStyle::PositionHint::CENTER, nvb::BlockWidgetStyle::PositionHint::TOP)
                    ));
        });

        boost::thread t([]() {
            nvb::Server::create(8080);
        });
        /*TODO: Find way to make a tcp request and check the servers response. Similar to how netcat works in bash*/
       // t.interrupt();
        t.join();
    }

BOOST_AUTO_TEST_SUITE_END()
