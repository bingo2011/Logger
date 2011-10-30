project(Logger4Cxx)
cmake_minimum_required(VERSION 2.6)
set(${SRC} log.cc)
add_executable(logger main.cpp ${SRC})