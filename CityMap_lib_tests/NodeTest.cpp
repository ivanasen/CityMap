#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "Node.hpp"
#include "Vertex.hpp"
#include <memory>

TEST_CASE("addNeighbour adds correctly", "[NodeTest]") {
    Node<int> n1(5);
    std::shared_ptr<Node<int>> n2 = std::make_shared<Node<int>>(10);
    std::shared_ptr<Node<int>> n3 = std::make_shared<Node<int>>(13);

    n1.addNeighbour(n2, 10);
    n1.addNeighbour(n3, 13);
    std::vector<Vertex<int>> neighbours = n1.getNeighbours();
    REQUIRE(neighbours[0] == Vertex(n2, 10));
    REQUIRE(neighbours[1] == Vertex(n3, 13));
}

TEST_CASE("addNeighbour does not add duplicates", "[NodeTest]") {
    Node<int> n1(5);
    auto n2 = std::make_shared<Node<int>>(10);

    n1.addNeighbour(n2, 10);
    n1.addNeighbour(n2, 12);

    std::vector<Vertex<int>> neighbours = n1.getNeighbours();
    REQUIRE(neighbours.size() == 1);
}

TEST_CASE("removeNeighbour works correclty", "[NodeTest]") {
    Node<int> n1(5);
    auto n2 = std::make_shared<Node<int>>(10);
    auto n3 = std::make_shared<Node<int>>(12);

    n1.addNeighbour(n2, 1);

    REQUIRE(n1.removeNeighbour(n2));
    REQUIRE_FALSE(n1.removeNeighbour(n3));
}