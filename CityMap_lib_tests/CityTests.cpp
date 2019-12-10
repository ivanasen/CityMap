#include <include/DeadEndFinder.h>
#include "catch.hpp"
#include "City.h"

TEST_CASE("addCrossroad works correctly", "[CityTests]") {
    CityMapLib::City city;
    std::string expected1 = "crossroad1";
    std::string expected2 = "crossroad2";

    city.addCrossroad(expected1);
    city.addCrossroad(expected2);
    std::vector<CityMapLib::CrossroadPtr> crossroads = city.getCrossroads();

    REQUIRE(crossroads[0]->getName() == expected1);
    REQUIRE(crossroads[1]->getName() == expected2);
}

TEST_CASE("addCrossroad ignores duplicate crossroad", "[CityTests]") {
    CityMapLib::City city;
    std::string expected1 = "crossroad1";

    city.addCrossroad(expected1);
    city.addCrossroad(expected1);

    std::vector<CityMapLib::CrossroadPtr> crossroads = city.getCrossroads();

    REQUIRE(crossroads.size() == 1);
}

TEST_CASE("addRoad works correctly", "[CityTests]") {
    CityMapLib::City city;
    std::string from = "from";
    std::string to = "to";
    int weight = 5;

    city.addCrossroad(from);
    city.addCrossroad(to);

    city.addRoad(from, to, weight);

    CityMapLib::CrossroadPtr fromPtr = city.getCrossroadByName(from);
    CityMapLib::CrossroadPtr toPtr = city.getCrossroadByName(to);
    std::vector<CityMapLib::Road> roads = fromPtr->getOutgoingRoads();

    REQUIRE(roads[0].getCrossroad().lock() == toPtr);
    REQUIRE(roads[0].getWeight() == weight);
}

TEST_CASE("removeRoad works correctly", "[CityTests]") {
    CityMapLib::City city;
    std::string from = "from";
    std::string to = "to";
    int weight = 5;

    city.addCrossroad(from);
    city.addCrossroad(to);

    city.addRoad(from, to, weight);
    city.removeRoad(from, to);

    CityMapLib::CrossroadPtr fromPtr = city.getCrossroadByName(from);

    REQUIRE(fromPtr->getOutgoingRoads().empty());
}