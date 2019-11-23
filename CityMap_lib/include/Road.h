#ifndef CITYMAP_ROAD_H
#define CITYMAP_ROAD_H

#include <memory>
#include <utility>
#include "Crossroad.h"

class Crossroad;

typedef std::shared_ptr<Crossroad> CrossroadPtr;

class Road {
private:
    int weight;
    CrossroadPtr crossroad;

public:
    Road(CrossroadPtr crossroad, int weight)
            : crossroad(std::move(crossroad)), weight(weight) {}

    Road &operator=(const Road &other) {
        weight = other.getWeight();
        crossroad = other.getCrossroad();
        return *this;
    }

    bool operator==(const Road &other) const {
        return weight == other.getWeight() && crossroad == other.getCrossroad();
    }

    [[nodiscard]] int getWeight() const {
        return weight;
    }

    [[nodiscard]] const CrossroadPtr &getCrossroad() const {
        return crossroad;
    }
};

#endif //CITYMAP_ROAD_H