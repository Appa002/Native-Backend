project(routing_Router_tests)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD ${GLOBAL_CXX_STANDARD})


set(Boost_ADDITIONAL_VERSIONS "1.58" "1.58.0")
find_package(Boost 1.58 REQUIRED COMPONENTS unit_test_framework system)

add_executable(routing_Router_tests_test_executable tests.cpp)
target_include_directories(routing_Router_tests_test_executable PRIVATE ${Boost_INCLUDE_DIRS})
include_directories(routing_Router_tests_test_executable ../../../header)
target_compile_definitions(routing_Router_tests_test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")

target_link_libraries(routing_Router_tests_test_executable ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(routing_Router_tests_test_executable ${Boost_SYSTEM_LIBRARY})
target_link_libraries(routing_Router_tests_test_executable pthread)
target_link_libraries(routing_Router_tests_test_executable native-backend)

add_test(NAME routing_Router_tests COMMAND routing_Router_tests_test_executable)