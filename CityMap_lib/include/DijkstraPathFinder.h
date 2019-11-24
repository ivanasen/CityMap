#ifndef CITYMAP_DIJKSTRAPATHFINDER_H
#define CITYMAP_DIJKSTRAPATHFINDER_H

#include <queue>
#include <utility>
#include "PathFinder.h"
#include "City.h"

namespace CityMapLib {

    class DijkstraPathFinder : public PathFinder {
    private:
        const City &city;
    public:
        explicit DijkstraPathFinder(const City &city);

        [[nodiscard]] bool hasPath(const std::string &from, const std::string &to) const override;

        [[nodiscard]] std::vector<Path> findBestPaths(
                const std::string &from,
                const std::string &to,
                unsigned int pathsCount) const override;
    };

}

#endif //CITYMAP_DIJKSTRAPATHFINDER_H
