#include <utility>
#include "Crossroad.h"

namespace CityMapLib {

    Crossroad::Crossroad(std::string name) : name(std::move(name)) {
    }

    void Crossroad::addRoadTo(const CrossroadPtr &crossroad, int weight) {
        roads.emplace_back(crossroad, weight);
    }

    bool Crossroad::removeRoadTo(const CrossroadPtr &crossroad) {
        for (size_t i = 0; i < roads.size(); ++i) {
            if (roads[i].getCrossroad() == crossroad) {
                roads[i] = roads.back();
                roads.pop_back();
                return true;
            }
        }

        return false;
    }

    std::string Crossroad::getName() const {
        return name;
    }

    const std::vector<Road> &Crossroad::getRoads() const {
        return roads;
    }

    bool Crossroad::operator==(const Crossroad &other) const {
        return name == other.getName();
    }

    void Crossroad::setBlocked(bool isBlocked) {
        blocked = isBlocked;
    }

}