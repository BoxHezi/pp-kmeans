cmake_minimum_required(VERSION 3.10)
project(eculidean_distance)
set(NAME "eculidean_distance")

find_path(CMAKE_FOLDER NAMES cmake/emp-tool-config.cmake)
include(${CMAKE_FOLDER}/cmake/common.cmake)
include(${CMAKE_FOLDER}/cmake/enable_rdseed.cmake)
include(${CMAKE_FOLDER}/cmake/enable_float.cmake)

set(CMAKE_CXX_STANDARD 14)

find_package(emp-tool REQUIRED)
find_package(emp-ot REQUIRED)
include_directories(${EMP-OT_INCLUDE_DIRS} ${EMP-TOOL_INCLUDE_DIRS})

# Installation
install(FILES cmake/secret-sharing-config.cmake DESTINATION cmake/)
install(DIRECTORY eculidean_distance DESTINATION include/)

ENABLE_TESTING()
ADD_SUBDIRECTORY(test)
