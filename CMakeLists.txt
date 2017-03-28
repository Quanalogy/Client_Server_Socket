cmake_minimum_required(VERSION 3.5.2)
project(file_client)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Client/TCPClient.cpp Client/TCPClient.h)
add_executable(file_client ${SOURCE_FILES})