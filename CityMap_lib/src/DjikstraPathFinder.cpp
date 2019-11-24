#include "DjikstraPathFinder.h"

namespace CityMapLib {

    DjikstraPathFinder::DjikstraPathFinder(const City &city) : city(city) {
    }

    bool DjikstraPathFinder::hasPath(const std::string &from, const std::string &to) const {
        return !getBestPaths(from, to, 1).empty();
    }

    std::vector<std::vector<CrossroadPtr>>
    DjikstraPathFinder::getBestPaths(const std::string &from, const std::string &to, unsigned int pathsCount) const {
        CrossroadPtr fromPtr = city.getCrossroadByName(from);
        CrossroadPtr toPtr = city.getCrossroadByName(to);


        return {};
    }

}