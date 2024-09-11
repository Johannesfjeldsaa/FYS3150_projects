cmake_minimum_required(VERSION 3.11)

project(Project1)

add_executable(problem2 solutions/problem2.cpp)

add_subdirectory(../externals/armadillo armadillo_build)
