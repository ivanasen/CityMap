cmake_minimum_required(VERSION 3.13)
project(CityMap)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/Catch)

add_subdirectory(src/CityMap_lib)
add_subdirectory(src/CityMap_cli)
add_subdirectory(src/CityMap_utils)
add_subdirectory(src/CityMap_serialization)

add_subdirectory(tests)