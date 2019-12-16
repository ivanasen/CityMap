#include "City.h"

#include <memory>

namespace citymap::lib {

    void City::addCrossroad(const std::string &crossroad) {
        if (crossroadIndexes.find(crossroad) != crossroadIndexes.end())
            return;

        CrossroadPtr crossroadPtr = std::make_shared<Crossroad>(crossroads.size(), crossroad);
        crossroadIndexes.insert({crossroad, crossroads.size()});
        crossroads.push_back(crossroadPtr);
    }

    void City::addRoad(const std::string &from, const std::string &to, int weight) {
        if (crossroadIndexes.find(from) == crossroadIndexes.end()) {
            addCrossroad(from);
        }

        if (crossroadIndexes.find(to) == crossroadIndexes.end()) {
            addCrossroad(to);
        }

        CrossroadPtr fromPtr = getCrossroadByName(from);
        CrossroadPtr toPtr = getCrossroadByName(to);
        fromPtr->addRoadTo(toPtr, weight);
        toPtr->addRoadFrom(fromPtr, weight);
    }

    bool City::removeRoad(const std::string &from, const std::string &to) {
        CrossroadPtr fromPtr = getCrossroadByName(from);
        CrossroadPtr toPtr = getCrossroadByName(to);
        return fromPtr && toPtr && fromPtr->removeRoadTo(toPtr) && toPtr->removeRoadFrom(fromPtr);
    }

    const std::vector<CrossroadPtr> &City::getCrossroads() const {
        return crossroads;
    }

    CrossroadPtr City::getCrossroadByName(const std::string &name) const {
        auto iter = crossroadIndexes.find(name);
        if (iter == crossroadIndexes.end()) {
            return nullptr;
        }

        return crossroads[iter->second];
    }

}