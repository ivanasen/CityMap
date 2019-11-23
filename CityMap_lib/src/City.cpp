#include "City.h"

#include <memory>

void City::addCrossroad(const std::string &crossroad) {
    CrossroadPtr crossroadPtr = std::make_shared<Crossroad>(crossroad);
    crossroads.insert({crossroad, crossroadPtr});
}

void City::addRoad(const std::string &from, const std::string &to, int weight) {
    auto iterFrom = crossroads.find(from);
    auto iterTo = crossroads.find(to);

    if (iterFrom == crossroads.end())
        throwInvalidCrossroad(from);
    if (iterTo == crossroads.end())
        throwInvalidCrossroad(to);

    iterFrom->second->addRoadTo(iterTo->second, weight);
}

unsigned long City::removeRoad(const std::string &from, const std::string &to) {
    auto iterFrom = crossroads.find(from);
    auto iterTo = crossroads.find(to);

    if (iterFrom == crossroads.end())
        throwInvalidCrossroad(from);
    if (iterTo == crossroads.end())
        throwInvalidCrossroad(to);

    return iterFrom->second->removeRoadTo(iterTo->second);
}

void City::throwInvalidCrossroad(const std::string &crossroad) {
    throw std::invalid_argument("Crossroad " + crossroad + " does not exist in this city.");
}

bool City::hasRoadBetween(const std::string &from, const std::string &to) const {
    return false;
}
