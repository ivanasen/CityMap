#ifndef CITYMAP_VERTEX_HPP
#define CITYMAP_VERTEX_HPP

#include <memory>
#include "Node.hpp"

template<typename T>
class Node;

template<typename T>
class Vertex {
private:
    int weight;
    std::shared_ptr<Node<T>> node;

public:
    Vertex(const std::shared_ptr<Node<T>> &node, int weight)
            : node(node), weight(weight) {}

    Vertex &operator=(const Vertex &other) {
        weight = other.weight;
        node = other.node;
        return *this;
    }

    bool operator==(const Vertex<T> &other) const {
        return weight == other.weight && node == other.node;
    }

    [[nodiscard]] int getWeight() const {
        return weight;
    }

    const std::shared_ptr<Node<T>> &getNode() const {
        return node;
    }
};

#endif //CITYMAP_VERTEX_HPP