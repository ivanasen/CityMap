#include "catch.hpp"

#include "CityTraveller.h"
#include "City.h"

namespace citymap::lib::tests {

    TEST_CASE("getCurrentLocation when city is empty return nullptr", "[CityTravellerTests]") {
        auto city = std::make_shared<City>();
        CityTraveller traveller(city);
        REQUIRE(traveller.getCurrentLocation() == nullptr);
    }

    TEST_CASE("getCurrentLocation returns first added crossroad", "[CityTravellerTests]") {
        auto city = std::make_shared<City>();
        CityTraveller traveller(city);

        city->addCrossroad("test");

        REQUIRE(traveller.getCurrentLocation() == city->getCrossroadByName("test"));
    }

    TEST_CASE("changeLocation with valid input changes currentLocation and returns true", "[CityTravellerTests]") {
        auto city = std::make_shared<City>();
        CityTraveller traveller(city);

        city->addCrossroad("0");
        city->addCrossroad("1");

        REQUIRE(traveller.changeLocation("1"));
        REQUIRE(traveller.getCurrentLocation() == city->getCrossroadByName("1"));

        REQUIRE(traveller.changeLocation("0"));
        REQUIRE(traveller.getCurrentLocation() == city->getCrossroadByName("0"));

        city->addCrossroad("3");
        REQUIRE(traveller.changeLocation("3"));
        REQUIRE(traveller.getCurrentLocation() == city->getCrossroadByName("3"));
    }

    TEST_CASE("changeLocation with invalid crossroad returns false and doesn't change currentLocation",
              "[CityTravellerTests]") {
        auto city = std::make_shared<City>();
        CityTraveller traveller(city);

        city->addCrossroad("0");

        REQUIRE_FALSE(traveller.changeLocation("1"));
        REQUIRE(traveller.getCurrentLocation() == city->getCrossroadByName("0"));

        REQUIRE_FALSE(traveller.changeLocation("2"));
        REQUIRE(traveller.getCurrentLocation() == city->getCrossroadByName("0"));
    }

}