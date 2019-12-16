#include <CycleFinder.h>
#include <DeadEndFinder.h>
#include "MapManager.h"

namespace citymap::cli {

    MapManager::MapManager(lib::City &city) : city(city), pathFinder(city) {
    }

    void MapManager::addCrossroad(const std::string &crossroad) {
        city.addCrossroad(crossroad);
    }

    void MapManager::addRoad(const std::string &from, const std::string &to, int weight) {
        city.addRoad(from, to, weight);
    }

    bool MapManager::removeRoad(const std::string &from, const std::string &to) {
        requireCrossroadExists(from);
        requireCrossroadExists(to);

        return city.removeRoad(from, to);
    }

    bool MapManager::hasPath(const std::basic_string<char> &from, const std::basic_string<char> &to) {
        requireCrossroadExists(from);
        requireCrossroadExists(to);

        return pathFinder.hasPath(from, to);
    }

    std::vector<lib::Path>
    MapManager::findShortestPaths(const std::string &from, const std::string &to, int maxPathsCount) {
        requireCrossroadExists(from);
        requireCrossroadExists(to);

        return pathFinder.findShortestPaths(from, to, maxPathsCount);
    }

    void MapManager::requireCrossroadExists(const std::string &crossroad) const {
        if (!city.getCrossroadByName(crossroad)) {
            throw std::invalid_argument("Crossroad " + crossroad + " doesn't exist");
        }
    }

    bool MapManager::setCrossroadClosed(const std::string &crossroad, bool closed) {
        requireCrossroadExists(crossroad);

        lib::CrossroadPtr crossroadPtr = city.getCrossroadByName(crossroad);

        if (crossroadPtr->isClosed() == closed) {
            return false;
        }

        crossroadPtr->setClosed(closed);
        return true;
    }

    bool MapManager::hasCycleFrom(const std::string &crossroad) {
        requireCrossroadExists(crossroad);
        return lib::CycleFinder::hasCycle(city, crossroad);
    }

    std::vector<lib::CrossroadPtr> MapManager::findEulerCycle() {
        return lib::CycleFinder::findEulerCycle(city);
    }

    bool MapManager::canReachAllFrom(const std::string &crossroad) {
        requireCrossroadExists(crossroad);
        return pathFinder.hasPathToAll(crossroad);
    }

    std::vector<std::pair<lib::CrossroadPtr, lib::CrossroadPtr>> MapManager::findDeadEnds() {
        return lib::DeadEndFinder::findDeadEnds(city);
    }

    void MapManager::setCity(lib::City &newCity) {
        city = newCity;
        pathFinder.setCity(city);
    }

}