cmake_minimum_required(VERSION 3.15)
project(CityMap_lib_tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(CityMap_tests_run CrossroadTests.cpp CityTests.cpp DijkstraPathFinderTests.cpp DeadEndFinderTests.cpp)
target_link_libraries(CityMap_tests_run CityMap_lib)