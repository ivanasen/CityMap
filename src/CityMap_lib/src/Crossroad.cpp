#include <utility>
#include "Crossroad.h"

namespace citymap::lib {

    Crossroad::Crossroad(int id, std::string name) : id(id), name(std::move(name)) {
    }

    void Crossroad::addRoadTo(const std::weak_ptr<Crossroad> &crossroad, int weight) {
        std::shared_ptr<Crossroad> ptr = crossroad.lock();

        auto iter = outgoingIndexes.find(ptr->getId());
        if (iter != outgoingIndexes.end()) {
            outgoingRoads[iter->second] = Road(crossroad, weight);
            return;
        }

        outgoingIndexes[ptr->getId()] = outgoingRoads.size();
        outgoingRoads.emplace_back(crossroad, weight);
    }

    bool Crossroad::removeRoadTo(const std::weak_ptr<Crossroad> &crossroad) {
        auto iter = outgoingIndexes.find(crossroad.lock()->getId());

        if (iter == outgoingIndexes.end()) {
            return false;
        }

        outgoingRoads[iter->second] = outgoingRoads.back();
        outgoingRoads.pop_back();

        outgoingIndexes[outgoingRoads.size() - 1] = iter->second;
        outgoingIndexes.erase(iter->first);

        return true;
    }

    void Crossroad::addRoadFrom(const std::weak_ptr<Crossroad> &crossroad, int weight) {
        std::shared_ptr<Crossroad> ptr = crossroad.lock();

        auto iter = incomingIndexes.find(ptr->getId());
        if (iter != incomingIndexes.end()) {
            incomingRoads[iter->second] = Road(crossroad, weight);
            return;
        }

        incomingIndexes[ptr->getId()] = incomingRoads.size();
        incomingRoads.emplace_back(crossroad, weight);
    }

    bool Crossroad::removeRoadFrom(const std::weak_ptr<Crossroad> &crossroad) {
        auto iter = incomingIndexes.find(crossroad.lock()->getId());

        if (iter == incomingIndexes.end()) {
            return false;
        }

        incomingRoads[iter->second] = incomingRoads.back();
        incomingRoads.pop_back();

        incomingIndexes[outgoingRoads.size() - 1] = iter->second;
        incomingIndexes.erase(iter->first);

        return true;
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

    void Crossroad::setClosed(bool isClosed) {
        closed = isClosed;
    }

    int Crossroad::getId() const {
        return id;
    }

    bool Crossroad::isClosed() const {
        return closed;
    }

    const std::vector<Road> &Crossroad::getIncomingRoads() const {
        return incomingRoads;
    }

    std::string Crossroad::toString() const {
        return name;
    }

}