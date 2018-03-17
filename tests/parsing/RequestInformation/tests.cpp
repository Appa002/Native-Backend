#define BOOST_TEST_MODULE parsing_RequestInformation_tests
#include <boost/test/unit_test.hpp>
#include <native-backend/parsing/RequestInformation.h>

BOOST_TEST_DONT_PRINT_LOG_VALUE(nvb::HttpVerb::Verb)

BOOST_AUTO_TEST_SUITE(parsing_RequestInformation_tests)

BOOST_AUTO_TEST_CASE( simple_request_parsing ){
    std::string sampleRequest = "GET /test?a=1&b=2 HTTP/1.1\n"
            "Host: localhost:8080\n"
            "User-Agent: Mozilla/5.0 Firefox/58.0\n"
            "Accept: text/html\n"
            "Accept-Language: en-US,en;q=0.5\n"
            "Accept-Encoding: gzip, deflate\n"
            "Connection: keep-alive\n"
            "Upgrade-Insecure-Requests: 1\n"
            "Pragma: no-cache\n"
            "Cache-Control: no-cache";

        auto info = nvb::RequestInformation::create(sampleRequest);
        BOOST_CHECK_EQUAL(info->path, "/test");
        BOOST_CHECK_EQUAL(info->params.at("a"), "1");
        BOOST_CHECK_EQUAL(info->params.at("b"), "2");
        BOOST_CHECK_EQUAL(info->http_verb, nvb::HttpVerb::Verb::get);

    }

BOOST_AUTO_TEST_SUITE_END()
