#define BOOST_TEST_MODULE server_server_tests
#include <boost/test/unit_test.hpp>
#include <native-backend/server/Server.h>


BOOST_AUTO_TEST_SUITE(server_server_tests)

    BOOST_AUTO_TEST_CASE( first ){
        BOOST_ASSERT(testFunc());
    }

BOOST_AUTO_TEST_SUITE_END()
