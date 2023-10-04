cmake_minimum_required(VERSION 3.21)
project(UDP_tftp C)
link_libraries(ws2_32)

set(CMAKE_C_STANDARD 99)

add_executable(UDP_tftp main.c)
