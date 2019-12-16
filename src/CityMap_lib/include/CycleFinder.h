#ifndef CITYMAP_CYCLEFINDER_H
#define CITYMAP_CYCLEFINDER_H

#include <vector>
#include "City.h"
#include "Path.h"

namespace citymap::lib {

    class CycleFinder {
    public:
        static bool hasCycle(const City &city, const std::string &startName);

        static bool hasEulerCycle(const City &city);

        static Path findEulerCycle(const City &city);

    private:
        static City getTransposeCity(const City &city);

        static bool isStronglyConnected(const City &city);

        static CrossroadPtr findConnectedNode(const std::vector<CrossroadPtr> &crossroads);
    };

}

#endif //CITYMAP_CYCLEFINDER_H
