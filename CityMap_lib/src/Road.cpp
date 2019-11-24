#include "Road.h"

#include <utility>

namespace CityMapLib {

    Road::Road(CrossroadPtr crossroad, int weight)
            : crossroad(std::move(crossroad)), weight(weight) {
    }

    bool Road::operator==(const Road &other) const {
        return weight == other.getWeight() && crossroad == other.getCrossroad();
    }

    int Road::getWeight() const {
        return weight;
    }

    const CrossroadPtr &Road::getCrossroad() const {
        return crossroad;
    }

}