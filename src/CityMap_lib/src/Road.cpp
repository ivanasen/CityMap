#include "Road.h"

#include <utility>

namespace citymap::lib {

    Road::Road(std::weak_ptr<Crossroad> crossroad, int weight)
            : crossroad(std::move(crossroad)), weight(weight) {
    }

    bool Road::operator==(const Road &other) const {
        return weight == other.getWeight() && crossroad.lock() == other.getCrossroad().lock();
    }

    int Road::getWeight() const {
        return weight;
    }

    const std::weak_ptr<Crossroad> &Road::getCrossroad() const {
        return crossroad;
    }

    bool Road::operator!=(const Road &other) const {
        return !(*this == other);
    }

    void Road::setWeight(int newWeight) {
        this->weight = newWeight;
    }
}