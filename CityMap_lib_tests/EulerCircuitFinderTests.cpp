#include "City.h"
#include "EulerCircuitFinder.h"
#include "catch.hpp"

TEST_CASE("hasEulerCircuit returns true for an empty city", "[EulerCircuitFinder]") {
    CityMapLib::City c;
    REQUIRE(CityMapLib::EulerCircuitFinder::hasEulerCircuit(c));
}

TEST_CASE("hasEulerCircuit returns true for a city with only one crossroad", "[EulerCircuitFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    REQUIRE(CityMapLib::EulerCircuitFinder::hasEulerCircuit(c));
}

TEST_CASE("hasEulerCircuit returns false on a case with two crossroads with one road", "[EulerCircuitFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addRoad("0", "1", 1);
    REQUIRE_FALSE(CityMapLib::EulerCircuitFinder::hasEulerCircuit(c));
}

TEST_CASE("hasEulerCircuit returns true for simple cycle with 3 crossroads", "[EulerCircuitFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addCrossroad("2");
    c.addRoad("0", "1", 1);
    c.addRoad("1", "2", 1);
    c.addRoad("2", "0", 1);
    REQUIRE(CityMapLib::EulerCircuitFinder::hasEulerCircuit(c));
}

TEST_CASE("hasEulerCircuit returns true on an Euler city", "[EulerCircuitFinder]") {
    CityMapLib::City c;
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

    REQUIRE(CityMapLib::EulerCircuitFinder::hasEulerCircuit(c));
}

TEST_CASE("hasEulerCircuit returns false on euler components which aren't connected", "[EulerCircuitFinder]") {
    CityMapLib::City c;
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

    REQUIRE_FALSE(CityMapLib::EulerCircuitFinder::hasEulerCircuit(c));
}

TEST_CASE("hasEulerCircuit returns false on an non-Euler city", "[EulerCircuitFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addCrossroad("2");
    c.addCrossroad("3");

    c.addRoad("0", "1", 1);
    c.addRoad("1", "2", 1);
    c.addRoad("2", "3", 1);

    REQUIRE_FALSE(CityMapLib::EulerCircuitFinder::hasEulerCircuit(c));
}

TEST_CASE("findEulerCircuit works on empty city", "[EulerCircuitFinder]") {
    CityMapLib::City c;
    std::vector<CityMapLib::CrossroadPtr> expected;
    std::vector<CityMapLib::CrossroadPtr> circuit = CityMapLib::EulerCircuitFinder::findEulerCircuit(c);

    REQUIRE(circuit == expected);
}

TEST_CASE("findEulerCircuit returns correct circuit", "[EulerCircuitFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addCrossroad("2");
    c.addRoad("0", "1", 1);
    c.addRoad("1", "2", 1);
    c.addRoad("2", "0", 1);

    CityMapLib::CrossroadPtr c0 = c.getCrossroadByName("0");
    CityMapLib::CrossroadPtr c1 = c.getCrossroadByName("1");
    CityMapLib::CrossroadPtr c2 = c.getCrossroadByName("2");

    std::vector<CityMapLib::CrossroadPtr> expectedCircuit{c0, c1, c2, c0};
    std::vector<CityMapLib::CrossroadPtr> circuit = CityMapLib::EulerCircuitFinder::findEulerCircuit(c);

    REQUIRE(circuit == expectedCircuit);
}

TEST_CASE("findEulerCircuit returns correct circuit on a bigger city", "[EulerCircuitFinder]") {
    SECTION("Single strongly-connected component case") {
        CityMapLib::City c;
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

        std::vector<CityMapLib::CrossroadPtr> expectedCircuit{
                c.getCrossroadByName("0"),
                c.getCrossroadByName("2"),
                c.getCrossroadByName("1"),
                c.getCrossroadByName("0"),
                c.getCrossroadByName("3"),
                c.getCrossroadByName("4"),
                c.getCrossroadByName("0"),
        };
        std::vector<CityMapLib::CrossroadPtr> circuit = CityMapLib::EulerCircuitFinder::findEulerCircuit(c);

        REQUIRE(circuit == expectedCircuit);
    }

    SECTION("Multiple strongly-connected component case") {
        CityMapLib::City c;
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

        std::vector<CityMapLib::CrossroadPtr> expectedCircuit{
                c.getCrossroadByName("0"),
                c.getCrossroadByName("1"),
                c.getCrossroadByName("2"),
                c.getCrossroadByName("3"),
                c.getCrossroadByName("4"),
                c.getCrossroadByName("2"),
                c.getCrossroadByName("0"),
        };
        std::vector<CityMapLib::CrossroadPtr> circuit = CityMapLib::EulerCircuitFinder::findEulerCircuit(c);

        REQUIRE(circuit == expectedCircuit);
    }
}