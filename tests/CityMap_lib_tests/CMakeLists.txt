cmake_minimum_required(VERSION 3.13)
project(CityMap_lib_tests)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(CityMap_lib_tests_run ${SOURCE_FILES})
target_link_libraries(CityMap_lib_tests_run CityMap_lib Catch)