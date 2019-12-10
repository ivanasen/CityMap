#include "EulerTourFinder.h"
#include <stack>

namespace CityMapLib {

    bool EulerTourFinder::hasEulerTour(const City &city) {
        if (!isStronglyConnected(city))
            return false;

        std::vector<CrossroadPtr> crossroads = city.getCrossroads();

        for (const CrossroadPtr &c : crossroads) {
            if (c->getIncomingRoads().size() != c->getOutgoingRoads().size()) {
                return false;
            }
        }

        return true;
    }

    std::vector<CrossroadPtr> EulerTourFinder::findEulerTour(const City &city) {
        if (!hasEulerTour(city)) {
            throw std::invalid_argument("The city doesn't have a valid Euler tour.");
        }


        return {};
    }

    City EulerTourFinder::getTransposeCity(const City &city) {
        City transpose;

        const std::vector<CrossroadPtr> &crossroads = city.getCrossroads();

        for (const CrossroadPtr &crossroad : crossroads) {
            transpose.addCrossroad(crossroad->getName());
        }

        for (const CrossroadPtr &crossroad : crossroads) {
            for (const Road &outgoing : crossroad->getOutgoingRoads()) {
                const std::weak_ptr<Crossroad> &c = outgoing.getCrossroad();
                int weight = outgoing.getWeight();
                transpose.addRoad(c.lock()->getName(), crossroad->getName(), weight);
            }
        }

        return transpose;
    }

    // Checks if each node in the city with a degree bigger than 0
    // belongs to the same strongly connected component
    // Uses Kosajaru's DFS based algorithm
    bool EulerTourFinder::isStronglyConnected(const City &city) {
        const std::vector<CrossroadPtr> &crossroads = city.getCrossroads();

        if (crossroads.empty())
            return true;

        std::vector<bool> visited(crossroads.size());

        CrossroadPtr startNode;
        for (const CrossroadPtr &c : crossroads) {
            if (!c->getOutgoingRoads().empty()) {
                startNode = c;
                break;
            }
        }

        if (startNode == nullptr)
            return true;

        dfsUtil(visited, startNode);

        for (const CrossroadPtr &c : crossroads) {
            if (!c->getOutgoingRoads().empty() && !visited[c->getId()]) {
                return false;
            }
        }

        City transpose = getTransposeCity(city);
        startNode = transpose.getCrossroadByName(startNode->getName());
        visited.clear();
        visited.resize(crossroads.size());

        dfsUtil(visited, startNode);

        for (const CrossroadPtr &c : transpose.getCrossroads()) {
            if (!c->getOutgoingRoads().empty() && !visited[c->getId()]) {
                return false;
            }
        }

        return true;
    }

    void EulerTourFinder::dfsUtil(std::vector<bool> &visited, const CrossroadPtr &c) {
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