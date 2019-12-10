#include "City.h"
#include "EulerTourFinder.h"
#include "catch.hpp"

TEST_CASE("hasEulerTour returns true for an empty city", "[EulerTourFinder]") {
    CityMapLib::City c;
    REQUIRE(CityMapLib::EulerTourFinder::hasEulerTour(c));
}

TEST_CASE("hasEulerTour returns true for a city with only one crossroad", "[EulerTourFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    REQUIRE(CityMapLib::EulerTourFinder::hasEulerTour(c));
}

TEST_CASE("hasEulerTour returns false on a case with two crossroads with one road", "[EulerTourFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addRoad("0", "1", 1);
    REQUIRE_FALSE(CityMapLib::EulerTourFinder::hasEulerTour(c));
}

TEST_CASE("hasEulerTour returns true for simple cycle with 3 crossroads", "[EulerTourFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addCrossroad("2");
    c.addRoad("0", "1", 1);
    c.addRoad("1", "2", 1);
    c.addRoad("2", "0", 1);
    REQUIRE(CityMapLib::EulerTourFinder::hasEulerTour(c));
}

TEST_CASE("hasEulerTour works correctly on an Euler city", "[EulerTourFinder]") {
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

    REQUIRE(CityMapLib::EulerTourFinder::hasEulerTour(c));
}

TEST_CASE("hasEulerTour returns false on an non-Euler city", "[EulerTourFinder]") {
    CityMapLib::City c;
    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addCrossroad("2");
    c.addCrossroad("3");

    c.addRoad("0", "1", 1);
    c.addRoad("1", "2", 1);
    c.addRoad("2", "3", 1);

    REQUIRE_FALSE(CityMapLib::EulerTourFinder::hasEulerTour(c));
}