project(parser_parser_tests)
cmake_minimum_required(VERSION 3.0)

set(Boost_ADDITIONAL_VERSIONS "1.64" "1.64.0")
find_package(Boost 1.64 REQUIRED COMPONENTS unit_test_framework)

add_executable(test_executable tests.cpp ../../../source/parser/parser.cpp)
target_include_directories(test_executable PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")

target_link_libraries(test_executable ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME parser_parser_tests COMMAND test_executable)