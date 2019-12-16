cmake_minimum_required(VERSION 3.13)
project(CityMap_serialization_tests)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(CityMap_serialization_tests_run ${SOURCE_FILES})
target_link_libraries(CityMap_serialization_tests_run CityMap_lib CityMap_serialization CityMap_utils Catch)