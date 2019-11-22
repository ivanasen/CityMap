#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "Graph.h"

TEST_CASE("ExampleTest", "[CityMapLibTests]") {
    CHECK(8 == Graph::test(5, 3));
}