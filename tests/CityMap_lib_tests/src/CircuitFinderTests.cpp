#include "City.h"
#include "CycleFinder.h"
#include "catch.hpp"

namespace citymap::lib::tests {

    TEST_CASE("findEulerCycle returns true for an empty city", "[CycleFinder]") {
        City c;
        REQUIRE(CycleFinder::hasEulerCycle(c));
    }

    TEST_CASE("findEulerCycle returns true for a city with only one crossroad", "[CycleFinder]") {
        City c;
        c.addCrossroad("0");
        REQUIRE(CycleFinder::hasEulerCycle(c));
    }

    TEST_CASE("findEulerCycle returns false on a case with two crossroads with one road", "[CycleFinder]") {
        City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addRoad("0", "1", 1);
        REQUIRE_FALSE(CycleFinder::hasEulerCycle(c));
    }

    TEST_CASE("findEulerCycle returns true for simple cycle with 3 crossroads", "[CycleFinder]") {
        City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");
        c.addRoad("0", "1", 1);
        c.addRoad("1", "2", 1);
        c.addRoad("2", "0", 1);
        REQUIRE(CycleFinder::hasEulerCycle(c));
    }

    TEST_CASE("findEulerCycle returns true on an Euler city", "[CycleFinder]") {
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

        REQUIRE(CycleFinder::hasEulerCycle(c));
    }

    TEST_CASE("findEulerCycle returns false on euler components which aren't connected", "[CycleFinder]") {
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

        REQUIRE_FALSE(CycleFinder::hasEulerCycle(c));
    }

    TEST_CASE("findEulerCycle returns false on an non-Euler city", "[CycleFinder]") {
        City c;
        c.addCrossroad("0");
        c.addCrossroad("1");
        c.addCrossroad("2");
        c.addCrossroad("3");

        c.addRoad("0", "1", 1);
        c.addRoad("1", "2", 1);
        c.addRoad("2", "3", 1);

        REQUIRE_FALSE(CycleFinder::hasEulerCycle(c));
    }

    TEST_CASE("findEulerCycle works on empty city", "[CycleFinder]") {
        City c;
        Path expected({});
        Path circuit = CycleFinder::findEulerCycle(c);

        REQUIRE(circuit == expected);
    }

    TEST_CASE("findEulerCycle returns correct circuit", "[CycleFinder]") {
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

        Path expectedCircuit({c0, c1, c2, c0});
        Path circuit = CycleFinder::findEulerCycle(c);

        REQUIRE(circuit == expectedCircuit);
    }

    TEST_CASE("findEulerCycle returns correct circuit on a bigger city", "[CycleFinder]") {
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

            Path expectedCircuit({
                                         c.getCrossroadByName("0"),
                                         c.getCrossroadByName("2"),
                                         c.getCrossroadByName("1"),
                                         c.getCrossroadByName("0"),
                                         c.getCrossroadByName("3"),
                                         c.getCrossroadByName("4"),
                                         c.getCrossroadByName("0"),
                                 });
            Path circuit = CycleFinder::findEulerCycle(c);

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

            Path expectedCircuit({
                                         c.getCrossroadByName("0"),
                                         c.getCrossroadByName("1"),
                                         c.getCrossroadByName("2"),
                                         c.getCrossroadByName("3"),
                                         c.getCrossroadByName("4"),
                                         c.getCrossroadByName("2"),
                                         c.getCrossroadByName("0"),
                                 });
            Path circuit = CycleFinder::findEulerCycle(c);

            REQUIRE(circuit == expectedCircuit);
        }
    }

    TEST_CASE("hasCycle works", "[CycleFinder]") {
        SECTION("Returns false on single crossroad city") {
            City c;
            c.addCrossroad("test");
            REQUIRE_FALSE(CycleFinder::hasCycle(c, "test"));
        }

        SECTION("Returns false on single road city") {
            City c;
            c.addCrossroad("0");
            c.addCrossroad("1");

            c.addRoad("0", "1", 1);

            REQUIRE_FALSE(CycleFinder::hasCycle(c, "0"));
        }

        SECTION("Returns true on city with 2 crossroads and circuit") {
            City c;
            c.addCrossroad("0");
            c.addCrossroad("1");

            c.addRoad("0", "1", 1);
            c.addRoad("1", "0", 1);

            REQUIRE(CycleFinder::hasCycle(c, "0"));
        }

        SECTION("Returns true on city with 3 crossroads and circuit") {
            City c;
            c.addCrossroad("0");
            c.addCrossroad("1");
            c.addCrossroad("2");

            c.addRoad("0", "1", 1);
            c.addRoad("1", "2", 1);
            c.addRoad("2", "0", 1);

            REQUIRE(CycleFinder::hasCycle(c, "2"));
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

            REQUIRE(CycleFinder::hasCycle(c, "0"));
            REQUIRE_FALSE(CycleFinder::hasCycle(c, "4"));
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
                REQUIRE_FALSE(CycleFinder::hasCycle(city, c->getName()));
            }
        }

    }

}