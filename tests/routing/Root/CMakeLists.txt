project(routing_Root_tests)
cmake_minimum_required(VERSION 3.0)

set(Boost_ADDITIONAL_VERSIONS "1.66" "1.66.0")
find_package(Boost 1.66 REQUIRED COMPONENTS unit_test_framework)

add_executable(routing_Root_tests_test_executable tests.cpp)
target_include_directories(routing_Root_tests_test_executable PRIVATE ${Boost_INCLUDE_DIRS})
include_directories(routing_Root_tests_test_executable ../../../header)
target_compile_definitions(routing_Root_tests_test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")

target_link_libraries(routing_Root_tests_test_executable ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(routing_Root_tests_test_executable native-backend)

add_test(NAME routing_Root_tests COMMAND routing_Root_tests_test_executable)