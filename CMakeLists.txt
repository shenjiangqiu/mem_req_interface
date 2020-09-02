cmake_minimum_required(VERSION 3.10)
project(mem_req_interface)
set(CMAKE_CXX_STANDARD 17)

add_library(mem_req_interface mem_req_interface.cc)
target_include_directories(mem_req_interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
