#include <queue>
#include <unordered_set>
#include "DijkstraPathFinder.h"

namespace CityMapLib {

    DijkstraPathFinder::DijkstraPathFinder(const City &city) : city(city) {
    }

    bool DijkstraPathFinder::hasPath(const std::string &from, const std::string &to) const {
        return !findBestPaths(from, to, 1).empty();
    }

    std::vector<Path> DijkstraPathFinder::findBestPaths(
            const std::string &from,
            const std::string &to,
            unsigned int pathsCount) const {
        std::vector<CrossroadPtr> crossroads = city.getCrossroads();
        std::vector<int> shortestPathsCount(crossroads.size());

        CrossroadPtr fromPtr = city.getCrossroadByName(from);
        CrossroadPtr toPtr = city.getCrossroadByName(to);

        std::vector<Path> bestPaths;

        if (fromPtr->isBlocked() || toPtr->isBlocked())
            return bestPaths;

        std::priority_queue<Path, std::vector<Path>, Path::DistanceComparator> q;
        q.push(Path({fromPtr}, 0));

        while (!q.empty() && shortestPathsCount[toPtr->getId()] < pathsCount) {
            Path current = q.top();
            q.pop();

            CrossroadPtr currentCrossroad = current.getPath().back();

            shortestPathsCount[currentCrossroad->getId()]++;

            if (currentCrossroad == toPtr) {
                bestPaths.push_back(current);
            }

            if (shortestPathsCount[currentCrossroad->getId()] <= pathsCount) {
                for (const Road &p : currentCrossroad->getRoads()) {
                    if (!(p.getCrossroad()->isBlocked())) {
                        Path newPath = current.addToPath(p);
                        q.push(newPath);
                    }
                }
            }
        }

        return bestPaths;
    }
}