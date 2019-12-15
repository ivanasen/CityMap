#ifndef CITYMAP_CIRCUITFINDER_H
#define CITYMAP_CIRCUITFINDER_H

#include <vector>
#include "City.h"

namespace CityMapLib {

    class CircuitFinder {
    public:
        static bool hasCircuit(const City& city, const std::string &startName);

        static bool hasEulerCircuit(const City &city);

        static std::vector<CrossroadPtr> findEulerCircuit(const City &city);

    private:
        static City getTransposeCity(const City &city);

        static bool isStronglyConnected(const City &city);

        static CrossroadPtr findConnectedNode(const std::vector<CrossroadPtr> &crossroads);
    };

}

#endif //CITYMAP_CIRCUITFINDER_H
