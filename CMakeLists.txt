cmake_minimum_required(VERSION 3.6)
project(Client_Server_Socket)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Client/main.cpp)
add_executable(Client_Server_Socket ${SOURCE_FILES})