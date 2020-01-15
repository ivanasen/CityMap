#include <queue>
#include <utility>
#include "DeadEndFinder.h"
#include "DijkstraPathFinder.h"
#include "GraphUtilities.h"

namespace citymap::lib {

    DijkstraPathFinder::DijkstraPathFinder(std::shared_ptr<City> city) : city(std::move(city)) {
    }

    bool DijkstraPathFinder::hasPath(const CrossroadPtr &from, const CrossroadPtr &to) const {
        std::vector<CrossroadPtr> crossroads = city->getCrossroads();

        std::vector<bool> visited(crossroads.size());
        std::queue<int> q;

        q.push(from->getId());

        while (!q.empty()) {
            int currentCrossroad = q.front();
            q.pop();

            if (currentCrossroad == to->getId())
                return true;

            for (const Road &road : crossroads[currentCrossroad]->getOutgoingRoads()) {
                const std::weak_ptr<Crossroad> &weakPtr = road.getCrossroad();
                if (CrossroadPtr crossroad = weakPtr.lock()) {
                    int crossroadId = crossroad->getId();
                    if (!visited[crossroadId])
                        q.push(crossroadId);
                }
            }
        }

        return false;
    }

    std::vector<Path> DijkstraPathFinder::findShortestPaths(
            const CrossroadPtr &from,
            const CrossroadPtr &to,
            unsigned int pathsCount) const {
        std::vector<CrossroadPtr> crossroads = city->getCrossroads();
        std::vector<int> shortestPathsCount(crossroads.size());

        std::vector<Path> bestPaths;

        if (from->isClosed() || to->isClosed())
            return bestPaths;

        std::priority_queue<Path, std::vector<Path>, Path::DistanceComparator> q;
        q.push(Path({from}, 0));

        while (!q.empty() && shortestPathsCount[to->getId()] < pathsCount) {
            Path current = q.top();
            q.pop();

            CrossroadPtr currentCrossroad = current.getPath().back();

            shortestPathsCount[currentCrossroad->getId()]++;

            if (currentCrossroad == to) {
                bestPaths.push_back(current);
            }

            if (shortestPathsCount[currentCrossroad->getId()] <= pathsCount) {
                for (const Road &road : currentCrossroad->getOutgoingRoads()) {
                    const std::weak_ptr<Crossroad> &weakPtr = road.getCrossroad();
                    if (CrossroadPtr crossroad = weakPtr.lock()) {
                        if (!(crossroad->isClosed())) {
                            Path newPath = current.addToPath(road);
                            q.push(newPath);
                        }
                    }
                }
            }
        }

        return bestPaths;
    }

    bool DijkstraPathFinder::hasPathToAll(const CrossroadPtr &start) const {
        const std::vector<CrossroadPtr> &crossroads = city->getCrossroads();
        std::vector<bool> visited(crossroads.size());

        dfsUtil(visited, start);

        for (bool b : visited) {
            if (!b) {
                return false;
            }
        }

        return true;
    }
}