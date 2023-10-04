cmake_minimum_required(VERSION 3.21)
project(TCP_client C)
link_libraries(ws2_32)
set(CMAKE_C_STANDARD 99)

add_executable(TCP_client main.c)
