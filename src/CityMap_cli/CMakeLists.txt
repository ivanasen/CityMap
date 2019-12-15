cmake_minimum_required(VERSION 3.15)
project(CityMap_cli)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(CityMap_cli ${SOURCE_FILES})

target_link_libraries(CityMap_cli CityMap_lib)