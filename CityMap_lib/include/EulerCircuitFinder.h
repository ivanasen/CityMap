#ifndef CITYMAP_EULERCIRCUITFINDER_H
#define CITYMAP_EULERCIRCUITFINDER_H

#include <vector>
#include "City.h"

namespace CityMapLib {

    class EulerCircuitFinder {
    public:
        static bool hasEulerCircuit(const City &city);

        static std::vector<CrossroadPtr> findEulerCircuit(const City &city);

    private:
        static City getTransposeCity(const City &city);

        static bool isStronglyConnected(const City &city);

        static CrossroadPtr findConnectedNode(const std::vector<CrossroadPtr> &crossroads);
    };

}

#endif //CITYMAP_EULERCIRCUITFINDER_H
