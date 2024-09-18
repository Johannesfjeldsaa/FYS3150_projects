cmake_minimum_required(VERSION 3.14)

project(test_package)

add_executable(test_package test.cpp)

target_link_directories(test_package PRIVATE ../src/cpp/build/)
target_link_libraries(test_package test_package_lib)
