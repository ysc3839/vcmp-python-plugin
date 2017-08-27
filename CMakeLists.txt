cmake_minimum_required(VERSION 3.0)

project(vcmp-python-plugin)

add_subdirectory(pybind11)

add_library(${PROJECT_NAME} SHARED main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE pybind11::embed)

math(EXPR _CMAKE_BITS "${CMAKE_SIZEOF_VOID_P} * 8")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
set(OS_NAME "win")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
set(OS_NAME "linux")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${OS_NAME}${_CMAKE_BITS}")
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
