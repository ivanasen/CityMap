#include "City.h"

#include <memory>

namespace CityMapLib {

    void City::addCrossroad(const std::string &crossroad) {
        if (crossroadIndexes.find(crossroad) != crossroadIndexes.end())
            return;

        CrossroadPtr crossroadPtr = std::make_shared<Crossroad>(crossroad);
        crossroads.push_back(crossroadPtr);
        crossroadIndexes.insert({crossroad, crossroads.size() - 1});
    }

    void City::addRoad(const std::string &from, const std::string &to, int weight) {
        CrossroadPtr fromPtr = getCrossroadByName(from);
        CrossroadPtr toPtr = getCrossroadByName(to);
        fromPtr->addRoadTo(toPtr, weight);
    }

    bool City::removeRoad(const std::string &from, const std::string &to) {
        CrossroadPtr fromPtr = getCrossroadByName(from);
        CrossroadPtr toPtr = getCrossroadByName(to);
        return fromPtr->removeRoadTo(toPtr);
    }

    const std::vector<CrossroadPtr> &City::getCrossroads() const {
        return crossroads;
    }

    const CrossroadPtr &City::getCrossroadByName(const std::string &name) const {
        auto iter = crossroadIndexes.find(name);
        if (iter == crossroadIndexes.end())
            throw std::invalid_argument("Crossroad with name \"" + name + "\" does not exist in this city.");

        return crossroads[iter->second];
    }

}