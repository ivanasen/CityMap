#ifndef CITYMAP_PATHFINDER_H
#define CITYMAP_PATHFINDER_H

#include <string>
#include <vector>
#include "Crossroad.h"
#include "DijkstraPathFinder.h"
#include "Path.h"

namespace CityMapLib {

    class PathFinder {
    public:
        [[nodiscard]] virtual bool hasPath(const std::string &from, const std::string &to) const = 0;

        [[nodiscard]] virtual std::vector<Path>
        findBestPaths(const std::string &from, const std::string &to, unsigned int pathsCount) const = 0;
    };

}

#endif //CITYMAP_PATHFINDER_H
