cmake_minimum_required(VERSION 3.21)
project(7_TCP_server_fork C)
link_libraries(ws2_32)
set(CMAKE_C_STANDARD 99)

add_executable(7_TCP_server_fork main.c)
