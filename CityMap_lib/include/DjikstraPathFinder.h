#ifndef CITYMAP_DJIKSTRAPATHFINDER_H
#define CITYMAP_DJIKSTRAPATHFINDER_H

#include "PathFinder.h"
#include "City.h"

namespace CityMapLib {

    class DjikstraPathFinder : public PathFinder {
    private:
        const City &city;

    public:
        explicit DjikstraPathFinder(const City &city);

        [[nodiscard]] bool hasPath(const std::string &from, const std::string &to) const override;

        [[nodiscard]] std::vector<std::vector<CrossroadPtr>>
        getBestPaths(const std::string &from, const std::string &to, unsigned int pathsCount) const override;
    };

}

#endif //CITYMAP_DJIKSTRAPATHFINDER_H
