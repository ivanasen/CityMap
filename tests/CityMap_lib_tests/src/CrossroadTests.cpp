#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "Crossroad.h"
#include <memory>

namespace citymap::lib::tests {

    TEST_CASE("addRoadTo adds correctly", "[CrossroadTests]") {
        Crossroad c(0, "0");
        auto c1 = std::make_shared<Crossroad>(1, "1");
        auto c2 = std::make_shared<Crossroad>(2, "2");

        c.addRoadTo(c1, 10);
        c.addRoadTo(c2, 13);
        std::vector<Road> roads = c.getOutgoingRoads();
        REQUIRE(roads[0] == Road(c1, 10));
        REQUIRE(roads[1] == Road(c2, 13));
    }

    TEST_CASE("removeRoadTo works correctly", "[CrossroadTests]") {
        Crossroad c(0, "0");
        auto c1 = std::make_shared<Crossroad>(1, "1");
        auto c2 = std::make_shared<Crossroad>(2, "2");

        c.addRoadTo(c1, 1);

        REQUIRE(c.removeRoadTo(c1));
        REQUIRE_FALSE(c.removeRoadTo(c2));
    }

}