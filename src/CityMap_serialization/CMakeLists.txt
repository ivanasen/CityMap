cmake_minimum_required(VERSION 3.15)
project(CityMap_serialization)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "src/*/*.cpp" "src/*.cpp" "src/*.h" "src/*/*.h")

include_directories(include/)

add_library(CityMap_serialization STATIC ${SOURCE_FILES})

target_link_libraries(CityMap_serialization PRIVATE CityMap_lib CityMap_utils)

target_include_directories(CityMap_serialization PUBLIC include/)