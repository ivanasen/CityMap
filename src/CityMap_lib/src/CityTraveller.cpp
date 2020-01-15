#include "CityTraveller.h"

#include <utility>
#include "Path.h"

namespace citymap::lib {

    CityTraveller::CityTraveller(const std::shared_ptr<City> &city)
            : city(city), pathFinder(city) {
    }

    CrossroadPtr CityTraveller::getCurrentLocation() const {
        return city->getCrossroadById(currentLocationId);
    }

    std::vector<CrossroadPtr> CityTraveller::getNeighbours() const {
        CrossroadPtr currentLocation = city->getCrossroadById(currentLocationId);

        if (!currentLocation) {
            return {};
        }

        std::vector<Road> outgoing = currentLocation->getOutgoingRoads();
        std::vector<CrossroadPtr> neighbours;
        neighbours.reserve(outgoing.size());

        for (const Road &road : outgoing) {
            neighbours.push_back(road.getCrossroad().lock());
        }

        return neighbours;
    }

    bool CityTraveller::changeLocation(const std::string &location) {
        CrossroadPtr newCrossroad = city->getCrossroadByName(location);
        if (!newCrossroad) {
            return false;
        }
        currentLocationId = newCrossroad->getId();
        return true;
    }

    Path CityTraveller::moveLocation(const std::string &location) {
        CrossroadPtr currentLocation = getCurrentLocation();
        CrossroadPtr targetLocation = city->getCrossroadByName(location);

        if (!currentLocation) {
            throw std::invalid_argument("The current city is empty.");
        }

        if (!targetLocation) {
            throw std::invalid_argument("The target crossroad " + location + " doesn't exist.");
        }

        std::vector<Path> paths = pathFinder.findShortestPaths(currentLocation, targetLocation, 1);

        if (paths.empty()) {
            throw std::invalid_argument(
                    "There is not path from " + currentLocation->toString() + " to " + location);
        }

        currentLocationId = paths[0].getPath().back()->getId();
        return paths[0];
    }

}