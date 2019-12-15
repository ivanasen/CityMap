#include <utility>
#include "Crossroad.h"

namespace CityMap::Lib {

    Crossroad::Crossroad(int id, std::string name) : id(id), name(std::move(name)) {
    }

    void Crossroad::addRoadTo(const std::weak_ptr<Crossroad> &crossroad, int weight) {
        std::weak_ptr<Crossroad> weakPtr(crossroad);
        outgoingRoads.emplace_back(weakPtr, weight);
    }

    bool Crossroad::removeRoadTo(const std::weak_ptr<Crossroad> &crossroad) {
        for (size_t i = 0; i < outgoingRoads.size(); ++i) {
            std::weak_ptr<Crossroad> ptr = outgoingRoads[i].getCrossroad();
            if (crossroad.lock() == ptr.lock()) {
                outgoingRoads[i] = outgoingRoads.back();
                outgoingRoads.pop_back();
                return true;
            }
        }

        return false;
    }

    void Crossroad::addRoadFrom(const std::weak_ptr<Crossroad> &crossroad, int weight) {
        std::weak_ptr<Crossroad> weakPtr(crossroad);
        incomingRoads.emplace_back(weakPtr, weight);
    }

    bool Crossroad::removeRoadFrom(const std::weak_ptr<Crossroad> &crossroad) {
        for (size_t i = 0; i < incomingRoads.size(); ++i) {
            std::weak_ptr<Crossroad> ptr = incomingRoads[i].getCrossroad();
            if (crossroad.lock() == ptr.lock()) {
                incomingRoads[i] = incomingRoads.back();
                incomingRoads.pop_back();
                return true;
            }
        }

        return false;
    }

    std::string Crossroad::getName() const {
        return name;
    }

    const std::vector<Road> &Crossroad::getOutgoingRoads() const {
        return outgoingRoads;
    }

    bool Crossroad::operator==(const Crossroad &other) const {
        return id == other.getId();
    }

    bool Crossroad::operator!=(const Crossroad &other) const {
        return !(*this == other);
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

    const std::vector<Road> &Crossroad::getIncomingRoads() const {
        return incomingRoads;
    }

}