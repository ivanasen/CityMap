#include "EulerCircuitFinder.h"
#include "GraphUtilities.h"
#include <stack>
#include <algorithm>

namespace CityMapLib {

    bool EulerCircuitFinder::hasEulerCircuit(const City &city) {
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

    std::vector<CrossroadPtr> EulerCircuitFinder::findEulerCircuit(const City &city) {
        if (!hasEulerCircuit(city)) {
            throw std::invalid_argument("The city doesn't have a valid Euler circuit.");
        }

        const std::vector<CrossroadPtr> &crossroads = city.getCrossroads();

        std::unordered_map<CrossroadPtr, std::vector<Road>> edgeCount;
        for (const CrossroadPtr &c : crossroads) {
            edgeCount[c] = c->getOutgoingRoads();
        }

        std::stack<CrossroadPtr> currPath;
        std::vector<CrossroadPtr> circuit;

        CrossroadPtr currNode = findConnectedNode(crossroads);

        if (!currNode)
            return circuit;

        currPath.push(currNode);

        while (!currPath.empty()) {
            if (!edgeCount[currNode].empty()) {
                currPath.push(currNode);

                Road nextRoad = edgeCount[currNode].back();
                edgeCount[currNode].pop_back();
                currNode = nextRoad.getCrossroad().lock();
            } else {
                circuit.push_back(currNode);

                currNode = currPath.top();
                currPath.pop();
            }
        }

        std::reverse(circuit.begin(), circuit.end());

        return circuit;
    }

    City EulerCircuitFinder::getTransposeCity(const City &city) {
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
    bool EulerCircuitFinder::isStronglyConnected(const City &city) {
        const std::vector<CrossroadPtr> &crossroads = city.getCrossroads();

        if (crossroads.empty())
            return true;

        std::vector<bool> visited(crossroads.size());

        CrossroadPtr startNode = findConnectedNode(crossroads);
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

    CrossroadPtr EulerCircuitFinder::findConnectedNode(const std::vector<CrossroadPtr> &crossroads) {
        for (const CrossroadPtr &c : crossroads) {
            if (!c->getOutgoingRoads().empty()) {
                return c;
            }
        }
        return nullptr;
    }

}