#include "DeadEndFinder.h"
#include <stack>

namespace CityMapLib {

    std::vector<std::pair<CrossroadPtr, CrossroadPtr>> DeadEndFinder::findDeadEnds(const City &city) {
        const std::vector<CrossroadPtr> &crossroads = city.getCrossroads();

        if (crossroads.size() < 2)
            return {};

        std::vector<bool> visited(crossroads.size());
        std::vector<std::pair<CrossroadPtr, CrossroadPtr>> deadEnds;

        for (size_t currCrossroad = 0; currCrossroad < crossroads.size(); ++currCrossroad) {
            if (visited[currCrossroad])
                continue;

            findDeadEndsFrom(currCrossroad, deadEnds, visited, crossroads);
        }

        return deadEnds;
    }

    void DeadEndFinder::findDeadEndsFrom(
            int start,
            std::vector<std::pair<CrossroadPtr, CrossroadPtr>> &deadEnds,
            std::vector<bool> &visited,
            const std::vector<CrossroadPtr> &crossroads) {
        std::stack<int> s;
        s.push(start);
        visited[start] = true;

        while (!s.empty()) {
            int currId = s.top();
            CrossroadPtr currentCrossroad = crossroads[currId];
            s.pop();

            std::vector<Road> currentRoads = currentCrossroad->getOutgoingRoads();

            for (const Road &road : crossroads[currId]->getOutgoingRoads()) {
                std::weak_ptr<Crossroad> nextWeakPtr = road.getCrossroad();

                if (CrossroadPtr nextCrossroad = nextWeakPtr.lock()) {
                    int nextId = nextCrossroad->getId();

                    if (!visited[nextId]) {
                        if (nextCrossroad->getOutgoingRoads().empty())
                            deadEnds.emplace_back(crossroads[currId], nextWeakPtr);
                        else
                            s.push(nextId);
                    }

                    visited[nextId] = true;
                }
            }
        }
    }

}