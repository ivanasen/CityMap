#include "CityTraveller.h"

#include <utility>

namespace citymap::cli {

    CityTraveller::CityTraveller(const MapManager &mapManager)
            : city(mapManager.getCity()), mapManager(mapManager) {
        if (city->getCrossroads().empty()) {
            return;
        }

        // By default set current location to first crossroad
        currentLocation = city->getCrossroads()[0];
    }

    lib::CrossroadPtr CityTraveller::getCurrentLocation() const {
        return currentLocation;
    }

    std::vector<lib::CrossroadPtr> CityTraveller::getNeighbours() const {
        std::vector<lib::Road> outgoing = currentLocation->getOutgoingRoads();
        std::vector<lib::CrossroadPtr> neighbours;
        neighbours.reserve(outgoing.size());

        for (const lib::Road &road : outgoing) {
            neighbours.push_back(road.getCrossroad().lock());
        }

        return neighbours;
    }

    bool CityTraveller::changeLocation(const std::string &location) {
        lib::CrossroadPtr newCrossroad = city->getCrossroadByName(location);
        if (!newCrossroad) {
            return false;
        }
        currentLocation = newCrossroad;
        return true;
    }

    lib::Path CityTraveller::moveLocation(const std::string &location) {
        std::vector<lib::Path> paths = mapManager.findShortestPaths(currentLocation->getName(), location);

        if (paths.empty()) {
            throw std::invalid_argument(
                    "There is not path from " + currentLocation->toString() + " to " + location);
        }

        currentLocation = paths[0].getPath().back();
        return paths[0];
    }

}