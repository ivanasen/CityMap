#include "City.h"

#include <memory>

namespace CityMapLib {

    void City::addCrossroad(const std::string &crossroad) {
        if (crossroadIndexes.find(crossroad) != crossroadIndexes.end())
            return;

        std::shared_ptr<Crossroad> crossroadPtr = std::make_shared<Crossroad>(crossroads.size(), crossroad);
        crossroadIndexes.insert({crossroad, crossroads.size()});
        crossroads.push_back(crossroadPtr);
    }

    void City::addRoad(const std::string &from, const std::string &to, int weight) {
        std::shared_ptr<Crossroad> fromPtr = getCrossroadByName(from);
        std::shared_ptr<Crossroad> toPtr = getCrossroadByName(to);
        fromPtr->addRoadTo(toPtr, weight);
    }

    bool City::removeRoad(const std::string &from, const std::string &to) {
        std::shared_ptr<Crossroad> fromPtr = getCrossroadByName(from);
        std::shared_ptr<Crossroad> toPtr = getCrossroadByName(to);
        return fromPtr->removeRoadTo(toPtr);
    }

    const std::vector<std::shared_ptr<Crossroad>> &City::getCrossroads() const {
        return crossroads;
    }

    std::shared_ptr<Crossroad> City::getCrossroadByName(const std::string &name) const {
        auto iter = crossroadIndexes.find(name);
        if (iter == crossroadIndexes.end())
            throw std::invalid_argument("Crossroad with name \"" + name + "\" does not exist in this city.");

        return crossroads[iter->second];
    }
}