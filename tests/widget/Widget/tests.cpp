#define BOOST_TEST_MODULE widget_Widget_tests
#include <boost/test/unit_test.hpp>
#include <native-backend/widgets/DivWidget.h>
#include <native-backend/widgets/TextWidget.h>

BOOST_AUTO_TEST_SUITE(widget_Widget_tests)

BOOST_AUTO_TEST_CASE( basic_interface_test ){
        auto w = boost::movelib::unique_ptr<nvb::DivWidget>(new nvb::DivWidget(
                new nvb::TextWidget("Hello, World!")));

        std::string out = w->build("", 0);
        std::string expected = "<div><p>Hello, World!</p></div>";
        BOOST_CHECK_EQUAL(out, expected);
    }

BOOST_AUTO_TEST_SUITE_END()
