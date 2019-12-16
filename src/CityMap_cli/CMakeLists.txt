cmake_minimum_required(VERSION 3.15)
project(CityMap_cli)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "src/*.cpp" "src/*.h" "src/*/*.cpp" "src/*/*.h")

add_executable(CityMap_cli ${SOURCE_FILES} src/MapFileManager.cpp src/MapFileManager.h)

target_link_libraries(CityMap_cli CityMap_lib CityMap_utils CityMap_serialization)