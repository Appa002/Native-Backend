#define BOOST_TEST_MODULE parsing_TextProcessor_tests

#include <boost/test/unit_test.hpp>
#include <native-backend/parsing/TextProcessor.h>
#include <iostream>

BOOST_AUTO_TEST_SUITE(parsing_TextProcessor_tests)

    BOOST_AUTO_TEST_CASE(simple_replacement) {
        std::unordered_map<std::string, std::string> replacements;
        replacements["[INSERT HERE]"] = "Bob";
        replacements["[AGE]"] = "3 Billion";

        std::string subject = "Hello, [INSERT HERE], how was your day? I see you're [AGE] years old! [INSERT HERE] [INSERT HERE] [INSERT HERE]";
        nvb::TextProcessor::process(&subject, replacements);
        BOOST_CHECK_EQUAL(subject, "Hello, Bob, how was your day? I see you're 3 Billion years old! Bob Bob Bob");
    }

BOOST_AUTO_TEST_SUITE_END()
