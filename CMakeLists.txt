cmake_minimum_required(VERSION 3.0)
project(Native-Backend VERSION 1.0.0 DESCRIPTION "Library for creating backends in c++")
enable_testing()


FILE(GLOB SOURCE_FILES
        source/native-backend/*/*.cpp)

FILE(GLOB HEADER_FILES
        header/native-backend/*/*.h)


add_library(native-backend SHARED ${SOURCE_FILES} ${HEADER_FILES})
include_directories(native-backend header)

add_subdirectory(tests/parser/parser)
add_subdirectory(tests/server/Server)
add_subdirectory(tests/db/DataBaseRecord)
add_subdirectory(tests/controller/Controller)
add_subdirectory(tests/widget/Widget)
add_subdirectory(tests/routing/Root)
add_subdirectory(tests/packaging/Bundle)