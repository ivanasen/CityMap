#include "DeadEndFinder.h"
#include <stack>

namespace citymap::lib {

    std::vector<std::pair<CrossroadPtr, CrossroadPtr>> DeadEndFinder::findDeadEnds(const City &city) {
        const std::vector<CrossroadPtr> &crossroads = city.getCrossroads();
        std::vector<std::pair<CrossroadPtr, CrossroadPtr>> deadEnds;

        for (const CrossroadPtr &crossroad : crossroads) {
            if (!crossroad->getOutgoingRoads().empty()) {
                continue;
            }

            for (const Road &road : crossroad->getIncomingRoads()) {
                deadEnds.emplace_back(road.getCrossroad(), crossroad);
            }
        }

        return deadEnds;
    }

}