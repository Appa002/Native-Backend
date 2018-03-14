#define BOOST_TEST_MODULE server_Server_tests

#include <boost/test/unit_test.hpp>
#include <native-backend/server/Server.h>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread/thread.hpp>

using boost::asio::ip::tcp;

BOOST_AUTO_TEST_SUITE(server_Server_tests)

    BOOST_AUTO_TEST_CASE(server_existents_check) {
        boost::thread t([]() {
            nvb::Server::create(8080);
        });
        /*TODO: Find way to make a tcp request and check the servers response. Similar to how netcat works in bash*/
        t.interrupt();
    }

BOOST_AUTO_TEST_SUITE_END()
