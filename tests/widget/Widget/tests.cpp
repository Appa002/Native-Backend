#define BOOST_TEST_MODULE widget_Widget_tests
#include <boost/test/unit_test.hpp>
#include <native-backend/widgets/TextWidget.h>

BOOST_AUTO_TEST_SUITE(widget_Widget_tests)

BOOST_AUTO_TEST_CASE( basic_interface_test ){
        auto w = boost::movelib::unique_ptr<nvb::IWidget>(
                new nvb::TextWidget("Hello, World!")
        );

        std::string out = w->build("", 0);
        std::string expected = R"(<span style="white-space: nowrap">Hello, World!</span>)";
        BOOST_CHECK_EQUAL(out, expected);
    }

BOOST_AUTO_TEST_SUITE_END()
