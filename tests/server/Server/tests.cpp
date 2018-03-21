#define BOOST_TEST_MODULE server_Server_tests

#include <boost/test/unit_test.hpp>
#include <native-backend/server/Server.h>
#include <boost/array.hpp>
#include <boost/thread/thread.hpp>
#include <native-backend/routing/Router.h>
#include <native-backend/widgets/IWidget.h>
#include <boost/move/unique_ptr.hpp>
#include <native-backend/widgets/TextWidget.h>
#include <native-backend/widgets/BlockViewWidget.h>
#include <native-backend/errors/HttpStatusCode.h>
#include <native-backend/widgets/ListViewWidget.h>

using boost::asio::ip::tcp;

BOOST_AUTO_TEST_SUITE(server_Server_tests)

    BOOST_AUTO_TEST_CASE(server_existents_check) {
        using namespace nvb;
        nvb::Router::getInstance()->addRoute(nvb::HttpVerb::Verb::get, "/", []() {

            auto myStyle = BlockViewWidgetStyle::createShared(
                    BlockViewWidgetStyle::PositionHint::CENTER,
                    BlockViewWidgetStyle::PositionHint::CENTER
            );

            auto view = ListViewWidget::createShared()
                    ->add(TextWidget::createShared("1"))
                    ->add(TextWidget::createShared("2"))
                    ->add(TextWidget::createShared("Hello, World!"));

            auto out = BlockViewWidget::createShared()
                    ->add(view)
                    ->setProperty({"style", myStyle});

            view->updateState();
            return out;

        });

        boost::thread t([]() {
            nvb::Server::create(8080);
        });
        /*TODO: Find way to make a tcp request and check the servers response. Similar to how netcat works in bash*/
        // t.interrupt();
        t.join();
    }

BOOST_AUTO_TEST_SUITE_END()
