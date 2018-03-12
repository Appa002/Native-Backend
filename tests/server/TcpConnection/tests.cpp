#define BOOST_TEST_MODULE server_TcpConnection_tests
#include <boost/test/unit_test.hpp>
#include <native-backend/server/Server.h>

BOOST_AUTO_TEST_SUITE(server_TcpConnection_tests)

    /*There's no use full way of testing this class outside of the
     * Server class, because one would require to mimic all behavior
     * of the Server class at which point you may as well just use
     * Server.*/

BOOST_AUTO_TEST_SUITE_END()
