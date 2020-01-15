#include "City.h"
#include "DijkstraPathFinder.h"
#include "Path.h"
#include "catch.hpp"

namespace citymap::lib::tests {

    TEST_CASE("hasPath works correctly", "[DijkstraPathFinder]") {
        std::shared_ptr<City> c = std::make_shared<City>();
        c->addCrossroad("0");
        c->addCrossroad("1");
        c->addCrossroad("2");
        c->addCrossroad("3");
        c->addCrossroad("4");

        c->addRoad("0", "1", 1);
        c->addRoad("1", "2", 1);
        c->addRoad("3", "2", 1);

        DijkstraPathFinder finder(c);

        CrossroadPtr c0 = c->getCrossroadByName("0");
        CrossroadPtr c1 = c->getCrossroadByName("1");
        CrossroadPtr c2 = c->getCrossroadByName("2");
        CrossroadPtr c3 = c->getCrossroadByName("3");
        CrossroadPtr c4 = c->getCrossroadByName("4");

        REQUIRE(finder.hasPath(c0, c1));
        REQUIRE(finder.hasPath(c1, c2));
        REQUIRE(finder.hasPath(c0, c2));
        REQUIRE(finder.hasPath(c3, c2));
        REQUIRE_FALSE(finder.hasPath(c0, c3));
        REQUIRE_FALSE(finder.hasPath(c1, c3));
        REQUIRE_FALSE(finder.hasPath(c2, c3));
        REQUIRE_FALSE(finder.hasPath(c0, c4));
        REQUIRE_FALSE(finder.hasPath(c1, c4));
        REQUIRE_FALSE(finder.hasPath(c2, c4));
        REQUIRE_FALSE(finder.hasPath(c3, c4));
    }

    TEST_CASE("findShortestPaths works correctly when there is no loop", "[DijkstraPathFinder]") {
        std::shared_ptr<City> c = std::make_shared<City>();
        c->addCrossroad("0");
        c->addCrossroad("1");
        c->addCrossroad("2");
        c->addCrossroad("3");

        CrossroadPtr c0 = c->getCrossroadByName("0");
        CrossroadPtr c1 = c->getCrossroadByName("1");
        CrossroadPtr c2 = c->getCrossroadByName("2");
        CrossroadPtr c3 = c->getCrossroadByName("3");

        c->addRoad("0", "1", 5);
        c->addRoad("0", "2", 6);
        c->addRoad("1", "3", 4);
        c->addRoad("2", "3", 2);

        DijkstraPathFinder finder(c);

        std::vector<Path> bestPaths = finder.findShortestPaths(c0, c3, 2);

        REQUIRE(bestPaths[0] == Path({c0, c2, c3}, 8));
        REQUIRE(bestPaths[1] == Path({c0, c1, c3}, 9));
    }

    TEST_CASE("findShortestPaths works when there is a loop", "[DijkstraPathFinder]") {
        std::shared_ptr<City> c = std::make_shared<City>();
        c->addCrossroad("0");
        c->addCrossroad("1");
        c->addCrossroad("2");

        c->addRoad("0", "1", 2);
        c->addRoad("1", "0", 3);
        c->addRoad("1", "2", 5);

        CrossroadPtr c0 = c->getCrossroadByName("0");
        CrossroadPtr c1 = c->getCrossroadByName("1");
        CrossroadPtr c2 = c->getCrossroadByName("2");

        DijkstraPathFinder finder(c);

        std::vector<Path> bestPaths = finder.findShortestPaths(c0, c2, 3);

        REQUIRE(bestPaths[0] == Path({c0, c1, c2}, 7));
        REQUIRE(bestPaths[1] == Path({c0, c1, c0, c1, c2}, 12));
        REQUIRE(bestPaths[2] == Path({c0, c1, c0, c1, c0, c1, c2}, 17));
    }

    TEST_CASE("findShortestPaths works when there are closed crossroads", "[DijkstraPathFinder]") {
        std::shared_ptr<City> c = std::make_shared<City>();
        c->addCrossroad("0");
        c->addCrossroad("1");
        c->addCrossroad("2");

        c->addRoad("0", "1", 1);
        c->addRoad("1", "2", 1);

        CrossroadPtr c0 = c->getCrossroadByName("0");
        CrossroadPtr c2 = c->getCrossroadByName("2");

        c->getCrossroadByName("1")->setClosed(true);

        DijkstraPathFinder finder(c);

        std::vector<Path> bestPaths = finder.findShortestPaths(c0, c2, 1);

        REQUIRE(bestPaths.empty());

        c->addRoad("0", "2", 10);

        std::vector<Path> bestPathsAfter = finder.findShortestPaths(c0, c2, 1);

        REQUIRE(bestPathsAfter[0] == Path({c0, c2}, 10));
    }

    TEST_CASE("hasPathToAll works", "[DijkstraPathFinder]") {
        SECTION("Single crossroad city") {
            std::shared_ptr<City> c = std::make_shared<City>();
            c->addCrossroad("test");
            DijkstraPathFinder f(c);

            REQUIRE(f.hasPathToAll(c->getCrossroadByName("test")));
        }

        SECTION("Small size city") {
            std::shared_ptr<City> c = std::make_shared<City>();
            c->addCrossroad("0");
            c->addCrossroad("1");
            c->addCrossroad("2");

            CrossroadPtr c0 = c->getCrossroadByName("0");
            CrossroadPtr c1 = c->getCrossroadByName("1");
            CrossroadPtr c2 = c->getCrossroadByName("2");

            c->addRoad("0", "1", 1);
            c->addRoad("1", "2", 1);
            c->addRoad("2", "0", 1);

            DijkstraPathFinder f(c);

            REQUIRE(f.hasPathToAll(c0));
        }

        SECTION("Medium size city") {
            std::shared_ptr<City> c = std::make_shared<City>();
            c->addCrossroad("0");
            c->addCrossroad("1");
            c->addCrossroad("2");
            c->addCrossroad("3");
            c->addCrossroad("4");

            c->addRoad("0", "1", 1);
            c->addRoad("1", "2", 1);
            c->addRoad("2", "3", 1);
            c->addRoad("3", "4", 1);
            c->addRoad("4", "2", 1);
            c->addRoad("2", "0", 1);

            DijkstraPathFinder f(c);
            REQUIRE(f.hasPathToAll(c->getCrossroadByName("0")));
        }

        SECTION("City with isolated crossroad") {
            std::shared_ptr<City> c = std::make_shared<City>();
            c->addCrossroad("0");
            c->addCrossroad("1");
            c->addCrossroad("2");
            c->addCrossroad("3");

            c->addRoad("0", "1", 1);
            c->addRoad("1", "2", 1);
            c->addRoad("2", "0", 1);

            DijkstraPathFinder f(c);
            REQUIRE_FALSE(f.hasPathToAll(c->getCrossroadByName("2")));
        }

        SECTION("City with single but not strongly connected component") {
            std::shared_ptr<City> c = std::make_shared<City>();
            c->addCrossroad("0");
            c->addCrossroad("1");
            c->addCrossroad("2");

            c->addRoad("0", "1", 1);
            c->addRoad("0", "2", 1);

            DijkstraPathFinder f(c);
            REQUIRE(f.hasPathToAll(c->getCrossroadByName("0")));

            REQUIRE_FALSE(f.hasPathToAll(c->getCrossroadByName("1")));
            REQUIRE_FALSE(f.hasPathToAll(c->getCrossroadByName("2")));
        }
    }
}