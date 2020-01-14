#include <CycleFinder.h>
#include <DeadEndFinder.h>

#include <utility>
#include "MapManager.h"

namespace citymap::cli {

    MapManager::MapManager(const std::shared_ptr<lib::City> &city) : city(city), pathFinder(city) {
    }

    void MapManager::addCrossroad(const std::string &crossroad) {
        city->addCrossroad(crossroad);
    }

    void MapManager::addRoad(const std::string &from, const std::string &to, int weight) {
        city->addRoad(from, to, weight);
    }

    bool MapManager::removeRoad(const std::string &from, const std::string &to) {
        requireCrossroadExists(from);
        requireCrossroadExists(to);

        return city->removeRoad(from, to);
    }

    bool MapManager::hasPath(const std::basic_string<char> &from, const std::basic_string<char> &to) const {
        requireCrossroadExists(from);
        requireCrossroadExists(to);

        return pathFinder.hasPath(from, to);
    }

    std::vector<lib::Path>
    MapManager::findShortestPaths(const std::string &from, const std::string &to, int maxPathsCount) const {
        requireCrossroadExists(from);
        requireCrossroadExists(to);

        return pathFinder.findShortestPaths(from, to, maxPathsCount);
    }

    void MapManager::requireCrossroadExists(const std::string &crossroad) const {
        if (!city->getCrossroadByName(crossroad)) {
            throw std::invalid_argument("Crossroad " + crossroad + " doesn't exist");
        }
    }

    bool MapManager::setCrossroadClosed(const std::string &crossroad, bool closed) {
        requireCrossroadExists(crossroad);

        lib::CrossroadPtr crossroadPtr = city->getCrossroadByName(crossroad);

        if (crossroadPtr->isClosed() == closed) {
            return false;
        }

        crossroadPtr->setClosed(closed);
        return true;
    }

    std::vector<lib::CrossroadPtr> MapManager::findClosedCrossroads() const {
        std::vector<lib::CrossroadPtr> closed;
        for (const auto &crossroad : city->getCrossroads()) {
            if (crossroad->isClosed()) {
                closed.push_back(crossroad);
            }
        }
        return std::vector<lib::CrossroadPtr>();
    }

    bool MapManager::hasCycleFrom(const std::string &crossroad) const {
        requireCrossroadExists(crossroad);
        return lib::CycleFinder::hasCycle(*city, crossroad);
    }

    lib::Path MapManager::findEulerCycle() const {
        return lib::CycleFinder::findEulerCycle(*city);
    }

    bool MapManager::canReachAllFrom(const std::string &crossroad) const {
        requireCrossroadExists(crossroad);
        return pathFinder.hasPathToAll(crossroad);
    }

    std::vector<std::pair<lib::CrossroadPtr, lib::CrossroadPtr>> MapManager::findDeadEnds() const {
        return lib::DeadEndFinder::findDeadEnds(*city);
    }

    const std::shared_ptr<lib::City> &MapManager::getCity() const {
        return city;
    }
}