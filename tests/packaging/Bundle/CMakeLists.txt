project(packaging_Bundle_tests)
cmake_minimum_required(VERSION 3.0)

set(Boost_ADDITIONAL_VERSIONS "1.64" "1.64.0")
find_package(Boost 1.64 REQUIRED COMPONENTS unit_test_framework)

add_executable(packaging_Bundle_tests_test_executable tests.cpp)
target_include_directories(packaging_Bundle_tests_test_executable PRIVATE ${Boost_INCLUDE_DIRS})
include_directories(packaging_Bundle_tests_test_executable ../../../header)
target_compile_definitions(packaging_Bundle_tests_test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")

target_link_libraries(packaging_Bundle_tests_test_executable ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(packaging_Bundle_tests_test_executable native-backend)

add_test(NAME packaging_Bundle_tests COMMAND packaging_Bundle_tests_test_executable)