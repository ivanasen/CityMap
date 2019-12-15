#include <stack>
#include "GraphUtilities.h"

namespace CityMap::Lib {

    void dfsUtil(std::vector<bool> &visited, const CrossroadPtr &c) {
        std::stack<CrossroadPtr> s;
        s.push(c);

        while (!s.empty()) {
            CrossroadPtr top = s.top();
            s.pop();

            visited[top->getId()] = true;

            for (const Road &road : top->getOutgoingRoads()) {
                CrossroadPtr crossroad = road.getCrossroad().lock();
                if (!visited[crossroad->getId()]) {
                    s.push(crossroad);
                }
            }
        }
    }

}
