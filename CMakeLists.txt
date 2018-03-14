cmake_minimum_required(VERSION 3.0)
project(Native-Backend VERSION 1.0.0 DESCRIPTION "Library for creating backends in c++")
enable_testing()

set(Boost_ADDITIONAL_VERSIONS "1.66" "1.66.0")
find_package(Boost 1.66 REQUIRED COMPONENTS system thread)

FILE(GLOB SOURCE_FILES
        source/native-backend/*/*.cpp)

FILE(GLOB HEADER_FILES
        header/native-backend/*/*.h)


add_library(native-backend SHARED ${SOURCE_FILES} ${HEADER_FILES})
include_directories(native-backend header)


target_include_directories(native-backend PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(native-backend ${Boost_SYSTEM_LIBRARY})
target_link_libraries(native-backend ${Boost_THREAD_LIBRARY})
#target_compile_definitions(widget_Widget_tests_test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")


add_subdirectory(tests/parser/parser)

add_subdirectory(tests/server/Server)
add_subdirectory(tests/server/TcpConnection)
add_subdirectory(tests/server/RequestInformation)

add_subdirectory(tests/packaging/Bundle)

add_subdirectory(tests/db/DataBaseRecord)

add_subdirectory(tests/widget/Widget)

add_subdirectory(tests/utils/Singleton)

add_subdirectory(tests/routing/Router)
