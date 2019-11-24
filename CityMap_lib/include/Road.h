#ifndef CITYMAP_ROAD_H
#define CITYMAP_ROAD_H

#include <memory>
#include <utility>
#include "Crossroad.h"

namespace CityMapLib {

    class Crossroad;

    typedef std::shared_ptr<Crossroad> CrossroadPtr;

    class Road {
    private:
        int weight;
        CrossroadPtr crossroad;

    public:
        Road(CrossroadPtr crossroad, int weight);

        bool operator==(const Road &other) const;

        [[nodiscard]] int getWeight() const;

        [[nodiscard]] const CrossroadPtr &getCrossroad() const;
    };

}

#endif //CITYMAP_ROAD_H