#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Crossroad.h"
#include <memory>

TEST_CASE("addRoadTo adds correctly", "[CrossroadTests]") {
    CityMapLib::Crossroad c(0, "0");
    auto c1 = std::make_shared<CityMapLib::Crossroad>(1 , "1");
    auto c2 = std::make_shared<CityMapLib::Crossroad>(2, "2");

    c.addRoadTo(c1, 10);
    c.addRoadTo(c2, 13);
    std::vector<CityMapLib::Road> roads = c.getRoads();
    REQUIRE(roads[0] == CityMapLib::Road(c1, 10));
    REQUIRE(roads[1] == CityMapLib::Road(c2, 13));
}

TEST_CASE("removeRoadTo works correctly", "[CrossroadTests]") {
    CityMapLib::Crossroad c(0, "0");
    auto c1 = std::make_shared<CityMapLib::Crossroad>(1, "1");
    auto c2 = std::make_shared<CityMapLib::Crossroad>(2, "2");

    c.addRoadTo(c1, 1);

    REQUIRE(c.removeRoadTo(c1));
    REQUIRE_FALSE(c.removeRoadTo(c2));
}