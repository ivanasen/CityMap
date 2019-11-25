#include "catch.hpp"
#include "DeadEndFinder.h"

TEST_CASE("DeadEndFinder doesn't find any dead-ends in city with less than 2 crossroads", "[DeadEndFinderTests]") {
    CityMapLib::City c;
    REQUIRE(CityMapLib::DeadEndFinder::findDeadEnds(c).empty());

    c.addCrossroad("0");
    REQUIRE(CityMapLib::DeadEndFinder::findDeadEnds(c).empty());
}

TEST_CASE("DeadEndFinder works correctly", "[DeadEndFinderTests]") {
    CityMapLib::City c;

    c.addCrossroad("0");
    c.addCrossroad("1");
    c.addCrossroad("2");

    c.addRoad("0", "1", 1);
    c.addRoad("0", "2", 1);

    std::vector<std::pair<CityMapLib::CrossroadPtr, CityMapLib::CrossroadPtr>> deadEnds =
            CityMapLib::DeadEndFinder::findDeadEnds(c);

    CityMapLib::CrossroadPtr cross0 = c.getCrossroadByName("0");
    CityMapLib::CrossroadPtr cross1 = c.getCrossroadByName("1");
    CityMapLib::CrossroadPtr cross2 = c.getCrossroadByName("2");

    REQUIRE(deadEnds[0] == std::make_pair(cross0, cross1));
    REQUIRE(deadEnds[1] == std::make_pair(cross0, cross2));
}