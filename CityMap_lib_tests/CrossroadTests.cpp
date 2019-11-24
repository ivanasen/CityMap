#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Crossroad.h"
#include <memory>

TEST_CASE("addRoadTo adds correctly", "[CrossroadTests]") {
    CityMapLib::Crossroad v1("test1");
    auto v2 = std::make_shared<CityMapLib::Crossroad>("test2");
    auto v3 = std::make_shared<CityMapLib::Crossroad>("test3");

    v1.addRoadTo(v2, 10);
    v1.addRoadTo(v3, 13);
    std::vector<CityMapLib::Road> roads = v1.getRoads();
    REQUIRE(roads[0] == CityMapLib::Road(v2, 10));
    REQUIRE(roads[1] == CityMapLib::Road(v3, 13));
}

TEST_CASE("removeRoadTo works correctly", "[CrossroadTests]") {
    CityMapLib::Crossroad v1("test1");
    auto v2 = std::make_shared<CityMapLib::Crossroad>("test2");
    auto v3 = std::make_shared<CityMapLib::Crossroad>("test3");

    v1.addRoadTo(v2, 1);

    REQUIRE(v1.removeRoadTo(v2));
    REQUIRE_FALSE(v1.removeRoadTo(v3));
}