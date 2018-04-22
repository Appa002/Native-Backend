project(server_server_tests)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD ${GLOBAL_CXX_STANDARD})

set(Boost_ADDITIONAL_VERSIONS ${GLOBAL_BOOST_VERSION} ${GLOBAL_BOOST_ADDITIONAL_VERSION})
find_package(Boost ${GLOBAL_BOOST_VERSION} REQUIRED COMPONENTS unit_test_framework system)

add_executable(server_server_tests_test_executable tests.cpp)
target_include_directories(server_server_tests_test_executable PRIVATE ${Boost_INCLUDE_DIRS})
include_directories(server_server_tests_test_executable ../../../header)
target_compile_definitions(server_server_tests_test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")

target_link_libraries(server_server_tests_test_executable ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(server_server_tests_test_executable ${Boost_SYSTEM_LIBRARY})
target_link_libraries(server_server_tests_test_executable pthread)
target_link_libraries(server_server_tests_test_executable native-backend)

add_test(NAME server_server_tests COMMAND server_server_tests_test_executable)