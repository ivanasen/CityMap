cmake_minimum_required(VERSION 3.15)
project(CityMap_lib)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(CityMap_lib INTERFACE)

target_include_directories(CityMap_lib INTERFACE ${PROJECT_SOURCE_DIR}/include/)
