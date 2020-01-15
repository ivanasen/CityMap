#ifndef CITYMAP_DIJKSTRAPATHFINDER_H
#define CITYMAP_DIJKSTRAPATHFINDER_H

#include <queue>
#include <utility>
#include "PathFinder.h"
#include "City.h"

namespace citymap::lib {

    class DijkstraPathFinder : public PathFinder {
    private:
        std::shared_ptr<City> city;
    public:
        explicit DijkstraPathFinder(std::shared_ptr<City> city);

        [[nodiscard]] bool hasPath(const CrossroadPtr &from, const CrossroadPtr &to) const override;

        bool hasPathToAll(const CrossroadPtr &start) const override;

        [[nodiscard]] std::vector<Path> findShortestPaths(
                const CrossroadPtr &from,
                const CrossroadPtr &to,
                unsigned int pathsCount) const override;
    };

}


#endif //CITYMAP_DIJKSTRAPATHFINDER_H
