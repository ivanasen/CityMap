#ifndef CITYMAP_ROAD_H
#define CITYMAP_ROAD_H

#include <memory>
#include <utility>
#include "Crossroad.h"

namespace CityMap::Lib {

    class Crossroad;

    class Road {
    private:
        int weight;
        std::weak_ptr<Crossroad> crossroad;

    public:
        Road(std::weak_ptr<Crossroad> crossroad, int weight);

        bool operator==(const Road &other) const;

        bool operator!=(const Road &other) const;

        [[nodiscard]] int getWeight() const;

        [[nodiscard]] const std::weak_ptr<Crossroad> &getCrossroad() const;
    };
}

#endif //CITYMAP_ROAD_H