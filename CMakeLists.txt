cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME vcmp-python-plugin)
project(${PROJECT_NAME})

add_subdirectory(pybind11)

add_library(${PROJECT_NAME} SHARED main.cpp ...)
target_link_libraries(${PROJECT_NAME} PRIVATE pybind11::embed)
