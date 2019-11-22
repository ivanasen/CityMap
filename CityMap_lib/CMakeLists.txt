cmake_minimum_required(VERSION 3.15)
project(CityMap_lib)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES Graph.cpp Graph.h)

set(SOURCE_FILES Graph.cpp Graph.cpp Graph.h Graph.cpp Graph.h)

add_library(CityMap_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})