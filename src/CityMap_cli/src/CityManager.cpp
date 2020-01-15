#include <CycleFinder.h>
#include <DeadEndFinder.h>

#include <utility>
#include "CityManager.h"

namespace citymap::cli {

    CityManager::CityManager(const std::shared_ptr<lib::City> &city) : city(city), pathFinder(city) {
    }

    void CityManager::addCrossroad(const std::string &crossroad) {
        city->addCrossroad(crossroad);
    }

    void CityManager::addRoad(const std::string &from, const std::string &to, int weight) {
        city->addRoad(from, to, weight);
    }

    bool CityManager::removeRoad(const std::string &from, const std::string &to) {
        getCrossroad(from);
        getCrossroad(to);

        return city->removeRoad(from, to);
    }

    bool CityManager::hasPath(const std::basic_string<char> &from, const std::basic_string<char> &to) const {
        getCrossroad(from);
        getCrossroad(to);

        return pathFinder.hasPath(from, to);
    }

    std::vector<lib::Path>
    CityManager::findShortestPaths(const std::string &from, const std::string &to, int maxPathsCount) const {
        lib::CrossroadPtr fromPtr = getCrossroad(from);
        lib::CrossroadPtr toPtr = getCrossroad(to);
        return pathFinder.findShortestPaths(fromPtr, toPtr, maxPathsCount);
    }

    lib::CrossroadPtr CityManager::getCrossroad(const std::string &crossroad) const {
        lib::CrossroadPtr c = city->getCrossroadByName(crossroad);
        if (!c) {
            throw std::invalid_argument("Crossroad " + crossroad + " doesn't exist");
        }
        return c;
    }

    bool CityManager::setCrossroadClosed(const std::string &crossroad, bool closed) {
        lib::CrossroadPtr crossroadPtr = getCrossroad(crossroad);

        if (crossroadPtr->isClosed() == closed) {
            return false;
        }

        crossroadPtr->setClosed(closed);
        return true;
    }

    std::vector<lib::CrossroadPtr> CityManager::findClosedCrossroads() const {
        std::vector<lib::CrossroadPtr> closed;
        for (const auto &crossroad : city->getCrossroads()) {
            if (crossroad->isClosed()) {
                closed.push_back(crossroad);
            }
        }
        return closed;
    }

    bool CityManager::hasCycleFrom(const std::string &crossroad) const {
        lib::CrossroadPtr crossroadPtr = getCrossroad(crossroad);
        return lib::CycleFinder::hasCycle(*city, crossroadPtr);
    }

    lib::Path CityManager::findEulerCycle() const {
        return lib::CycleFinder::findEulerCycle(*city);
    }

    bool CityManager::canReachAllFrom(const std::string &crossroad) const {
        getCrossroad(crossroad);
        return pathFinder.hasPathToAll(crossroad);
    }

    std::vector<std::pair<lib::CrossroadPtr, lib::CrossroadPtr>> CityManager::findDeadEnds() const {
        return lib::DeadEndFinder::findDeadEnds(*city);
    }

    const std::shared_ptr<lib::City> &CityManager::getCity() const {
        return city;
    }
}