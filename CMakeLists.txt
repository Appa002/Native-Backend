cmake_minimum_required(VERSION 3.0)
project(Native-Backend)


set(GLOBAL_CXX_STANDARD "17" CACHE STRING "The CXX Standard use in this project")
set(GLOBAL_BOOST_VERSION "1.66" CACHE STRING "The Version of Boost used in this Project")
set(GLOBAL_BOOST_ADDITIONAL_VERSIONS "1.66.0" CACHE STRING "The Additional Version of Boost used in this Project")


set(CMAKE_CXX_STANDARD ${GLOBAL_CXX_STANDARD})
enable_testing()


set(Boost_ADDITIONAL_VERSIONS ${GLOBAL_BOOST_VERSION} ${GLOBAL_BOOST_ADDITIONAL_VERSIONS})
set(BOOST_LIBRARYDIR "/usr/local/lib/boost/")
find_package(Boost ${GLOBAL_BOOST_VERSION} COMPONENTS system thread regex)

FILE(GLOB SOURCE_FILES
        source/native-backend/*/*.cpp)

FILE(GLOB HEADER_FILES
        header/native-backend/*/*.h)


add_library(native-backend SHARED ${SOURCE_FILES} ${HEADER_FILES})
include_directories(native-backend header)


target_include_directories(native-backend PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(native-backend ${Boost_SYSTEM_LIBRARY})
target_link_libraries(native-backend ${Boost_THREAD_LIBRARY})
target_link_libraries(native-backend ${Boost_REGEX_LIBRARY})
#target_compile_definitions(widget_Widget_tests_test_executable PRIVATE "BOOST_TEST_DYN_LINK=1")


add_subdirectory(tests/parsing/RequestInformation)
add_subdirectory(tests/parsing/TextProcessor)

add_subdirectory(tests/server/Server)
add_subdirectory(tests/server/TcpConnection)

add_subdirectory(tests/packaging/Bundle)

add_subdirectory(tests/db/DataBaseRecord)

add_subdirectory(tests/widget/Widget)

add_subdirectory(tests/utils/Singleton)

add_subdirectory(tests/routing/Router)
