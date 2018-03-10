cmake_minimum_required(VERSION 3.0)
project(Native-Backend VERSION 1.0.0 DESCRIPTION "Library for creating backends in c++")
enable_testing()

add_library(native-backend SHARED header/native-backend/parser/parser.h header/native-backend/server/Server.h source/native-backend/parser/parser.cpp source/native-backend/server/Server.cpp)
include_directories(native-backend header)

add_subdirectory(tests/parser/parser)
add_subdirectory(tests/server/server)