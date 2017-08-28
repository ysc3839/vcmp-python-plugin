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

execute_process(COMMAND "${PYTHON_EXECUTABLE}" "-c" "import sys;print(''.join(str(v) for v in sys.version_info[:2]));"
    OUTPUT_VARIABLE PYTHON_VER)
string(REGEX REPLACE "\n" "" PYTHON_VER ${PYTHON_VER})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-cpython${PYTHON_VER}-${OS_NAME}${_CMAKE_BITS}")
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
