#include "City.h"
#include "DijkstraPathFinder.h"
#include "Path.h"
#include "catch.hpp"

TEST_CASE("hasPath works correctly", "[DijkstraPathFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addCrossroad("2");
    c.addCrossroad("3");
    c.addCrossroad("4");

    c.addRoad("0", "1", 1);
    c.addRoad("1", "2", 1);
    c.addRoad("3", "2", 1);

    CityMapLib::DijkstraPathFinder finder(c);

    REQUIRE(finder.hasPath("0", "1"));
    REQUIRE(finder.hasPath("1", "2"));
    REQUIRE(finder.hasPath("0", "2"));
    REQUIRE(finder.hasPath("3", "2"));
    REQUIRE_FALSE(finder.hasPath("0", "3"));
    REQUIRE_FALSE(finder.hasPath("1", "3"));
    REQUIRE_FALSE(finder.hasPath("2", "3"));
    REQUIRE_FALSE(finder.hasPath("0", "4"));
    REQUIRE_FALSE(finder.hasPath("1", "4"));
    REQUIRE_FALSE(finder.hasPath("2", "4"));
    REQUIRE_FALSE(finder.hasPath("3", "4"));
}

TEST_CASE("findBestPaths works correctly when there is no loop", "[DijkstraPathFinder]") {
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

TEST_CASE("findBestPaths works when there is a loop", "[DijkstraPathFinder]") {
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

TEST_CASE("findBestPaths works when there are blocked crossroads", "[DijkstraPathFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addCrossroad("2");

    c.addRoad("0", "1", 1);
    c.addRoad("1", "2", 1);

    c.getCrossroadByName("1")->setBlocked(true);

    CityMapLib::DijkstraPathFinder finder(c);

    std::vector<CityMapLib::Path> bestPaths = finder.findBestPaths("0", "2", 1);

    REQUIRE(bestPaths.empty());

    c.addRoad("0", "2", 10);

    std::vector<CityMapLib::Path> bestPathsAfter = finder.findBestPaths("0", "2", 1);

    CityMapLib::CrossroadPtr cross0 = c.getCrossroadByName("0");
    CityMapLib::CrossroadPtr cross2 = c.getCrossroadByName("2");

    REQUIRE(bestPathsAfter[0] == CityMapLib::Path({cross0, cross2}, 10));
}

TEST_CASE("hasPathToAll works", "[DijkstraPathFinder]") {
    SECTION("Single crossroad city") {
        CityMapLib::City c;
        c.addCrossroad("test");
        CityMapLib::DijkstraPathFinder f(c);

        REQUIRE(f.hasPathToAll("test"));
    }

    SECTION("Small size city") {
        CityMapLib::City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");

        c.addRoad("0", "1", 1);
        c.addRoad("1", "2", 1);
        c.addRoad("2", "0", 1);

        CityMapLib::DijkstraPathFinder f(c);

        REQUIRE(f.hasPathToAll("0"));
    }

    SECTION("Medium size city") {
        CityMapLib::City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");
        c.addCrossroad("3");
        c.addCrossroad("4");

        c.addRoad("0", "1", 1);
        c.addRoad("1", "2", 1);
        c.addRoad("2", "3", 1);
        c.addRoad("3", "4", 1);
        c.addRoad("4", "2", 1);
        c.addRoad("2", "0", 1);

        CityMapLib::DijkstraPathFinder f(c);
        REQUIRE(f.hasPathToAll("0"));
    }

    SECTION("City with isolated crossroad") {
        CityMapLib::City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");
        c.addCrossroad("3");

        c.addRoad("0", "1", 1);
        c.addRoad("1", "2", 1);
        c.addRoad("2", "0", 1);

        CityMapLib::DijkstraPathFinder f(c);
        REQUIRE_FALSE(f.hasPathToAll("2"));
    }

    SECTION("City with single but not strongly connected component") {
        CityMapLib::City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");

        c.addRoad("0", "1", 1);
        c.addRoad("0", "2", 1);

        CityMapLib::DijkstraPathFinder f(c);
        REQUIRE(f.hasPathToAll("0"));

        REQUIRE_FALSE(f.hasPathToAll("1"));
        REQUIRE_FALSE(f.hasPathToAll("2"));
    }
}