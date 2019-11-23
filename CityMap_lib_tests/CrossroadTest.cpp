#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "Crossroad.h"
#include <memory>

TEST_CASE("addRoadTo adds correctly", "[NodeTest]") {
    Crossroad v1("test1");
    auto v2 = std::make_shared<Crossroad>("test2");
    auto v3 = std::make_shared<Crossroad>("test3");

    v1.addRoadTo(v2, 10);
    v1.addRoadTo(v3, 13);
    std::vector<Road> roads = v1.getRoads();
    REQUIRE(roads[0] == Road(v2, 10));
    REQUIRE(roads[1] == Road(v3, 13));
}

TEST_CASE("removeRoadTo works correctly", "[NodeTest]") {
    Crossroad v1("test1");
    auto v2 = std::make_shared<Crossroad>("test2");
    auto v3 = std::make_shared<Crossroad>("test3");

    v1.addRoadTo(v2, 1);

    REQUIRE(v1.removeRoadTo(v2));
    REQUIRE_FALSE(v1.removeRoadTo(v3));
}