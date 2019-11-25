#include <utility>
#include "Crossroad.h"

namespace CityMapLib {

    Crossroad::Crossroad(int id, std::string name) : id(id), name(std::move(name)) {
    }

    void Crossroad::addRoadTo(const std::shared_ptr<Crossroad> &crossroad, int weight) {
        std::weak_ptr<Crossroad> weakPtr(crossroad);
        roads.emplace_back(weakPtr, weight);
    }

    bool Crossroad::removeRoadTo(const std::shared_ptr<Crossroad> &crossroad) {
        for (size_t i = 0; i < roads.size(); ++i) {
            std::weak_ptr<Crossroad> ptr = roads[i].getCrossroad();
            if (crossroad == ptr.lock()) {
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
        return id == other.getId();
    }

    void Crossroad::setBlocked(bool isBlocked) {
        blocked = isBlocked;
    }

    int Crossroad::getId() const {
        return id;
    }

    bool Crossroad::isBlocked() const {
        return blocked;
    }
}