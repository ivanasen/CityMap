#ifndef CITYMAP_NODE_HPP
#define CITYMAP_NODE_HPP

#include <vector>
#include <memory>
#include "Vertex.hpp"

template<typename T>
class Node {
public:
    explicit Node(const T &value) : value(value) {
    }

    void addNeighbour(const std::shared_ptr<Node<T>> &neighbour, int weight) {
        if (findNeighbour(neighbour) == INDEX_NOT_FOUND)
            neighbours.emplace_back(neighbour, weight);
    }

    bool removeNeighbour(const std::shared_ptr<Node<T>> neighbour) {
        int index = findNeighbour(neighbour);

        if (index == INDEX_NOT_FOUND)
            return false;

        neighbours[index] = neighbours.back();
        neighbours.pop_back();
        return true;
    }

    T getValue() const {
        return value;
    }

    const std::vector<Vertex<T>> &getNeighbours() const {
        return neighbours;
    }

private:
    const int INDEX_NOT_FOUND = -1;

    const T value;
    std::vector<Vertex<T>> neighbours;

    int findNeighbour(const std::shared_ptr<Node<T>> &node) const {
        for (int i = 0; i < neighbours.size(); ++i) {
            if (neighbours[i].getNode() == node)
                return i;
        }
        return INDEX_NOT_FOUND;
    }
};

#endif //CITYMAP_NODE_HPP
