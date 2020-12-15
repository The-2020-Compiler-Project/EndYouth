cmake_minimum_required(VERSION 3.15)
project(untitled3)

set(CMAKE_CXX_STANDARD 14)
#add_library(untitled3 main.cpp byylf_cf.h byylf_cf.cpp)


add_executable(untitled3 main.cpp byylf_cf.cpp byylf_cf.h parse.cpp parse.h)
