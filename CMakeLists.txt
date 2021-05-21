cmake_minimum_required(VERSION 3.13)
project(pp_kmeans)

set(CMAKE_CXX_STANDARD 14)

add_executable(pp_kmeans main.cpp Point.cpp Point.h Cluster.cpp Cluster.h Party.cpp Party.h)