#include <include/City.h>
#include <include/DijkstraPathFinder.h>
#include "catch.hpp"

TEST_CASE("DijkstraPathFinder works correctly", "[PathFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addCrossroad("2");
    c.addCrossroad("3");

    c.addRoad("0", "1", 5);
    c.addRoad("0", "2", 6);
    c.addRoad("1", "3", 4);
    c.addRoad("2", "3", 2);

    CityMapLib::DijkstraPathFinder finder(c);

    std::vector<CityMapLib::Path> bestPaths = finder.findBestPaths("0", "3", 2);

    CityMapLib::CrossroadPtr cross0 = c.getCrossroadByName("0");
    CityMapLib::CrossroadPtr cross1 = c.getCrossroadByName("1");
    CityMapLib::CrossroadPtr cross2 = c.getCrossroadByName("2");
    CityMapLib::CrossroadPtr cross3 = c.getCrossroadByName("3");

    REQUIRE(bestPaths[0] == CityMapLib::Path({cross0, cross2, cross3}, 8));
    REQUIRE(bestPaths[1] == CityMapLib::Path({cross0, cross1, cross3}, 9));
}

TEST_CASE("DijkstraPathFinder when there is a loop", "[PathFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addCrossroad("2");

    c.addRoad("0", "1", 2);
    c.addRoad("1", "0", 3);
    c.addRoad("1", "2", 5);

    CityMapLib::DijkstraPathFinder finder(c);

    std::vector<CityMapLib::Path> bestPaths = finder.findBestPaths("0", "2", 3);

    CityMapLib::CrossroadPtr cross0 = c.getCrossroadByName("0");
    CityMapLib::CrossroadPtr cross1 = c.getCrossroadByName("1");
    CityMapLib::CrossroadPtr cross2 = c.getCrossroadByName("2");

    REQUIRE(bestPaths[0] == CityMapLib::Path({cross0, cross1, cross2}, 7));
    REQUIRE(bestPaths[1] == CityMapLib::Path({cross0, cross1, cross0, cross1, cross2}, 12));
    REQUIRE(bestPaths[2] == CityMapLib::Path({cross0, cross1, cross0, cross1, cross0, cross1, cross2}, 17));
}