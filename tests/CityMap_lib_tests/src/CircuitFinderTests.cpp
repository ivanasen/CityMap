#include "City.h"
#include "CircuitFinder.h"
#include "catch.hpp"

namespace CityMap::Lib::Tests {

    TEST_CASE("hasEulerCircuit returns true for an empty city", "[CircuitFinder]") {
        City c;
        REQUIRE(CircuitFinder::hasEulerCircuit(c));
    }

    TEST_CASE("hasEulerCircuit returns true for a city with only one crossroad", "[CircuitFinder]") {
        City c;
        c.addCrossroad("0");
        REQUIRE(CircuitFinder::hasEulerCircuit(c));
    }

    TEST_CASE("hasEulerCircuit returns false on a case with two crossroads with one road", "[CircuitFinder]") {
        City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addRoad("0", "1", 1);
        REQUIRE_FALSE(CircuitFinder::hasEulerCircuit(c));
    }

    TEST_CASE("hasEulerCircuit returns true for simple cycle with 3 crossroads", "[CircuitFinder]") {
        City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");
        c.addRoad("0", "1", 1);
        c.addRoad("1", "2", 1);
        c.addRoad("2", "0", 1);
        REQUIRE(CircuitFinder::hasEulerCircuit(c));
    }

    TEST_CASE("hasEulerCircuit returns true on an Euler city", "[CircuitFinder]") {
        City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");
        c.addCrossroad("3");
        c.addCrossroad("4");

        c.addRoad("0", "3", 1);
        c.addRoad("0", "2", 1);
        c.addRoad("1", "0", 1);
        c.addRoad("2", "1", 1);
        c.addRoad("3", "4", 1);
        c.addRoad("4", "0", 1);

        REQUIRE(CircuitFinder::hasEulerCircuit(c));
    }

    TEST_CASE("hasEulerCircuit returns false on euler components which aren't connected", "[CircuitFinder]") {
        City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");
        c.addCrossroad("3");
        c.addCrossroad("4");
        c.addCrossroad("5");

        c.addRoad("0", "1", 1);
        c.addRoad("1", "2", 1);
        c.addRoad("2", "1", 1);
        c.addRoad("3", "4", 1);
        c.addRoad("4", "5", 1);
        c.addRoad("5", "3", 1);

        REQUIRE_FALSE(CircuitFinder::hasEulerCircuit(c));
    }

    TEST_CASE("hasEulerCircuit returns false on an non-Euler city", "[CircuitFinder]") {
        City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");
        c.addCrossroad("3");

        c.addRoad("0", "1", 1);
        c.addRoad("1", "2", 1);
        c.addRoad("2", "3", 1);

        REQUIRE_FALSE(CircuitFinder::hasEulerCircuit(c));
    }

    TEST_CASE("findEulerCircuit works on empty city", "[CircuitFinder]") {
        City c;
        std::vector<CrossroadPtr> expected;
        std::vector<CrossroadPtr> circuit = CircuitFinder::findEulerCircuit(c);

        REQUIRE(circuit == expected);
    }

    TEST_CASE("findEulerCircuit returns correct circuit", "[CircuitFinder]") {
        City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");
        c.addRoad("0", "1", 1);
        c.addRoad("1", "2", 1);
        c.addRoad("2", "0", 1);

        CrossroadPtr c0 = c.getCrossroadByName("0");
        CrossroadPtr c1 = c.getCrossroadByName("1");
        CrossroadPtr c2 = c.getCrossroadByName("2");

        std::vector<CrossroadPtr> expectedCircuit{c0, c1, c2, c0};
        std::vector<CrossroadPtr> circuit = CircuitFinder::findEulerCircuit(c);

        REQUIRE(circuit == expectedCircuit);
    }

    TEST_CASE("findEulerCircuit returns correct circuit on a bigger city", "[CircuitFinder]") {
        SECTION("Single strongly-connected component case") {
            City c;
            c.addCrossroad("0");
            c.addCrossroad("1");
            c.addCrossroad("2");
            c.addCrossroad("3");
            c.addCrossroad("4");

            c.addRoad("0", "3", 1);
            c.addRoad("0", "2", 1);
            c.addRoad("1", "0", 1);
            c.addRoad("2", "1", 1);
            c.addRoad("3", "4", 1);
            c.addRoad("4", "0", 1);

            std::vector<CrossroadPtr> expectedCircuit{
                    c.getCrossroadByName("0"),
                    c.getCrossroadByName("2"),
                    c.getCrossroadByName("1"),
                    c.getCrossroadByName("0"),
                    c.getCrossroadByName("3"),
                    c.getCrossroadByName("4"),
                    c.getCrossroadByName("0"),
            };
            std::vector<CrossroadPtr> circuit = CircuitFinder::findEulerCircuit(c);

            REQUIRE(circuit == expectedCircuit);
        }

        SECTION("Multiple strongly-connected component case") {
            City c;
            c.addCrossroad("0");
            c.addCrossroad("1");
            c.addCrossroad("2");
            c.addCrossroad("3");
            c.addCrossroad("4");
            c.addCrossroad("5");

            c.addRoad("0", "1", 1);
            c.addRoad("1", "2", 1);
            c.addRoad("2", "3", 1);
            c.addRoad("3", "4", 1);
            c.addRoad("4", "2", 1);
            c.addRoad("2", "0", 1);

            std::vector<CrossroadPtr> expectedCircuit{
                    c.getCrossroadByName("0"),
                    c.getCrossroadByName("1"),
                    c.getCrossroadByName("2"),
                    c.getCrossroadByName("3"),
                    c.getCrossroadByName("4"),
                    c.getCrossroadByName("2"),
                    c.getCrossroadByName("0"),
            };
            std::vector<CrossroadPtr> circuit = CircuitFinder::findEulerCircuit(c);

            REQUIRE(circuit == expectedCircuit);
        }
    }

    TEST_CASE("hasCircuit works", "[CircuitFinder]") {
        SECTION("Returns false on single crossroad city") {
            City c;
            c.addCrossroad("test");
            REQUIRE_FALSE(CircuitFinder::hasCircuit(c, "test"));
        }

        SECTION("Returns false on single road city") {
            City c;
            c.addCrossroad("0");
            c.addCrossroad("1");

            c.addRoad("0", "1", 1);

            REQUIRE_FALSE(CircuitFinder::hasCircuit(c, "0"));
        }

        SECTION("Returns true on city with 2 crossroads and circuit") {
            City c;
            c.addCrossroad("0");
            c.addCrossroad("1");

            c.addRoad("0", "1", 1);
            c.addRoad("1", "0", 1);

            REQUIRE(CircuitFinder::hasCircuit(c, "0"));
        }

        SECTION("Returns true on city with 3 crossroads and circuit") {
            City c;
            c.addCrossroad("0");
            c.addCrossroad("1");
            c.addCrossroad("2");

            c.addRoad("0", "1", 1);
            c.addRoad("1", "2", 1);
            c.addRoad("2", "0", 1);

            REQUIRE(CircuitFinder::hasCircuit(c, "2"));
        }

        SECTION("Works on city with more crossroads") {
            City c;
            c.addCrossroad("0");
            c.addCrossroad("1");
            c.addCrossroad("2");
            c.addCrossroad("3");
            c.addCrossroad("4");

            c.addRoad("0", "1", 1);
            c.addRoad("1", "2", 1);
            c.addRoad("2", "3", 1);
            c.addRoad("3", "0", 1);
            c.addRoad("3", "4", 1);

            REQUIRE(CircuitFinder::hasCircuit(c, "0"));
            REQUIRE_FALSE(CircuitFinder::hasCircuit(c, "4"));
        }

        SECTION("Works on city with the form of a tree") {
            City city;
            city.addCrossroad("0");
            city.addCrossroad("1");
            city.addCrossroad("2");
            city.addCrossroad("3");
            city.addCrossroad("4");

            city.addRoad("0", "1", 1);
            city.addRoad("0", "2", 1);
            city.addRoad("1", "3", 1);
            city.addRoad("1", "4", 1);

            for (const CrossroadPtr &c : city.getCrossroads()) {
                REQUIRE_FALSE(CircuitFinder::hasCircuit(city, c->getName()));
            }
        }

    }

}