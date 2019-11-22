cmake_minimum_required(VERSION 3.15)
project(CityMap)

set(CMAKE_CXX_STANDARD 17)

include_directories(CityMap_lib)

add_subdirectory(CityMap_lib)
add_subdirectory(CityMap_lib_tests)