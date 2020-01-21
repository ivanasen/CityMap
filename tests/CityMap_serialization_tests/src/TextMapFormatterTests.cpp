#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <random>
#include <algorithm>
#include <City.h>
#include <TextMapFormatter.h>
#include "Strings.h"

namespace citymap::serialization::tests {

    TextMapFormatter formatter;

    static std::pair<lib::City, std::string>
    buildRandomCityWithExpectedSerialization(int crossroadCount, int maxRoadCount) {
        lib::City city;
        std::string expected;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> dist(1, crossroadCount);

        for (int i = 1; i <= crossroadCount; ++i) {
            std::string crossroadName = std::to_string(i);
            city.addCrossroad(crossroadName);
        }

        for (int i = 1; i <= crossroadCount; ++i) {
            std::string crossroadName = std::to_string(i);

            expected += crossroadName;

            int roadCount = dist(mt) % maxRoadCount;
            if (roadCount) {
                std::vector<int> roads(roadCount);
                for (int j = 0; j < roads.size(); ++j) {
                    roads[j] = j + 1;
                }
                std::shuffle(roads.begin(), roads.end(), mt);

                for (int j = 0; j < roadCount; ++j) {
                    std::string roadTo = std::to_string(roads.back());
                    int weight = dist(mt) + 1;
                    city.addRoad(crossroadName, roadTo, weight);
                    roads.pop_back();

                    expected += ' ' + roadTo + ' ' + std::to_string(weight);
                }
            }

            expected += '\n';
        }

        return {city, expected};
    }

    TEST_CASE("TextMapFormatter serializes correctly", "[TextMapFormatter]") {

        SECTION("Empty city") {
            lib::City c;

            std::string result = formatter.serialize(c);

            REQUIRE(result.empty());
        }

        SECTION("Single crossroad city") {
            lib::City c;

            std::string crossroadName = "Test";
            c.addCrossroad(crossroadName);

            std::string result = formatter.serialize(c);

            REQUIRE(result == crossroadName + TextMapFormatter::LINE_SEPARATOR);
        }

        SECTION("City with 3 crossroads without roads") {
            lib::City c;

            std::string crossroad1 = "Test1";
            std::string crossroad2 = "Test2";
            std::string crossroad3 = "Test3";
            c.addCrossroad(crossroad1);
            c.addCrossroad(crossroad2);
            c.addCrossroad(crossroad3);

            std::string result = formatter.serialize(c);

            std::string expected = crossroad1 + TextMapFormatter::LINE_SEPARATOR
                                   + crossroad2 + TextMapFormatter::LINE_SEPARATOR
                                   + crossroad3 + TextMapFormatter::LINE_SEPARATOR;

            REQUIRE(result == expected);
        }

        SECTION("City with 3 crossroads and roads") {
            lib::City c;

            std::string crossroad1 = "Test1";
            std::string crossroad2 = "Test2";
            std::string crossroad3 = "Test3";
            c.addCrossroad(crossroad1);
            c.addCrossroad(crossroad2);
            c.addCrossroad(crossroad3);

            c.addRoad(crossroad1, crossroad2, 10);
            c.addRoad(crossroad2, crossroad3, 345);
            c.addRoad(crossroad3, crossroad1, 1232);

            std::string result = formatter.serialize(c);

            std::string expected =
                    crossroad1 + ' ' + crossroad2 + ' ' + std::to_string(10) + '\n'
                    + crossroad2 + ' ' + crossroad3 + ' ' + std::to_string(345) + '\n'
                    + crossroad3 + ' ' + crossroad1 + ' ' + std::to_string(1232) + '\n';

            REQUIRE(result == expected);
        }

        SECTION("Small city with random roads and crossroads") {
            auto cityWithSerialization = buildRandomCityWithExpectedSerialization(10, 10);
            std::string serialized = formatter.serialize(cityWithSerialization.first);
            REQUIRE(serialized == cityWithSerialization.second);
        }

        SECTION("Medium city with random roads and crossroads") {
            auto cityWithSerialization = buildRandomCityWithExpectedSerialization(100, 100);
            REQUIRE(formatter.serialize(cityWithSerialization.first) == cityWithSerialization.second);
        }

        SECTION("Big city with random roads and crossroads") {
            auto cityWithSerialization = buildRandomCityWithExpectedSerialization(1000, 1000);
            REQUIRE(formatter.serialize(cityWithSerialization.first) == cityWithSerialization.second);
        }
    }

    TEST_CASE("TextMapFormatter deserializes correctly", "[TextMapFormatter]") {
        SECTION("Empty city") {
            lib::City city = formatter.deserialize("");

            REQUIRE(city.getCrossroads().empty());
        }

        SECTION("City with single crossroad") {
            auto expected = "test";

            lib::City city = formatter.deserialize(expected);

            const std::vector<lib::CrossroadPtr> &crossroads = city.getCrossroads();
            REQUIRE(crossroads.size() == 1);
            REQUIRE(crossroads[0]->getName() == expected);
        }

        SECTION("Serializing and rebuilding a random city back works") {
            auto cityWithSerialization = buildRandomCityWithExpectedSerialization(1000, 1000);
            lib::City city = cityWithSerialization.first;

            std::string expected = formatter.serialize(city);

            lib::City deserialized = formatter.deserialize(expected);

            std::vector<std::string> lines =
                    utils::Strings::split(formatter.serialize(deserialized), '\n');
            std::vector<std::string> expectedLines = utils::Strings::split(expected, '\n');

            std::unordered_set<std::string> linesSet;
            for (const std::string &s : lines) {
                linesSet.insert(s);
            }

            std::unordered_set<std::string> expectedSet;
            for (const std::string &s : expectedLines) {
                expectedSet.insert(s);
            }

            REQUIRE(linesSet == expectedSet);
        }
    }
}
