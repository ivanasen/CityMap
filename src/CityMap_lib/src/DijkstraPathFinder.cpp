#include <queue>
#include <utility>
#include "DeadEndFinder.h"
#include "DijkstraPathFinder.h"
#include "GraphUtilities.h"

namespace citymap::lib {

    DijkstraPathFinder::DijkstraPathFinder(std::shared_ptr<City> city) : city(std::move(city)) {
    }

    bool DijkstraPathFinder::hasPath(const std::string &from, const std::string &to) const {
        CrossroadPtr fromPtr = city->getCrossroadByName(from);
        CrossroadPtr toPtr = city->getCrossroadByName(to);
        std::vector<CrossroadPtr> crossroads = city->getCrossroads();

        if (!fromPtr) {
            throw std::invalid_argument("Crossroad doesn't exist: " + from);
        }

        if (!toPtr) {
            throw std::invalid_argument("Crossroad doesn't exist: " + to);
        }

        std::vector<bool> visited(crossroads.size());
        std::queue<int> q;

        q.push(fromPtr->getId());

        while (!q.empty()) {
            int currentCrossroad = q.front();
            q.pop();

            if (currentCrossroad == toPtr->getId())
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
            const std::string &from,
            const std::string &to,
            unsigned int pathsCount) const {
        std::vector<CrossroadPtr> crossroads = city->getCrossroads();
        std::vector<int> shortestPathsCount(crossroads.size());

        CrossroadPtr fromPtr = city->getCrossroadByName(from);
        CrossroadPtr toPtr = city->getCrossroadByName(to);

        std::vector<Path> bestPaths;

        if (fromPtr->isClosed() || toPtr->isClosed())
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
                for (const Road &p : currentCrossroad->getOutgoingRoads()) {
                    const std::weak_ptr<Crossroad> &weakPtr = p.getCrossroad();
                    if (CrossroadPtr crossroad = weakPtr.lock()) {
                        if (!(crossroad->isClosed())) {
                            Path newPath = current.addToPath(p);
                            q.push(newPath);
                        }
                    }
                }
            }
        }

        return bestPaths;
    }

    bool DijkstraPathFinder::hasPathToAll(const std::string &start) const {
        CrossroadPtr startNode = city->getCrossroadByName(start);
        const std::vector<CrossroadPtr> &crossroads = city->getCrossroads();
        std::vector<bool> visited(crossroads.size());

        dfsUtil(visited, startNode);

        for (bool b : visited) {
            if (!b) {
                return false;
            }
        }

        return true;
    }
}