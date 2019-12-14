cmake_minimum_required(VERSION 3.15)
project(CityMap_lib)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "src/*.cpp")

include_directories(include/)

add_library(CityMap_lib STATIC ${SOURCE_FILES} src/GraphUtilities.h src/GraphUtilites.cpp)

target_include_directories(CityMap_lib PUBLIC include/)
