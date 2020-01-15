#ifndef CITYMAP_PATHFINDER_H
#define CITYMAP_PATHFINDER_H

#include <string>
#include <vector>
#include "Crossroad.h"
#include "DijkstraPathFinder.h"
#include "Path.h"

namespace citymap::lib {

    class PathFinder {
    public:
        [[nodiscard]] virtual bool hasPath(const CrossroadPtr &from, const CrossroadPtr &to) const = 0;

        [[nodiscard]] virtual bool hasPathToAll(const CrossroadPtr &start) const = 0;

        [[nodiscard]] virtual std::vector<Path>
        findShortestPaths(const CrossroadPtr &from, const CrossroadPtr &to, unsigned int pathsCount) const = 0;
    };

}

#endif //CITYMAP_PATHFINDER_H
