#ifndef CITYMAP_CYCLEFINDER_H
#define CITYMAP_CYCLEFINDER_H

#include <vector>
#include "City.h"

namespace CityMap::Lib {

        class CycleFinder {
        public:
            static bool hasCycle(const City &city, const std::string &startName);

            static bool hasEulerCycle(const City &city);

            static std::vector<CrossroadPtr> findEulerCycle(const City &city);

        private:
            static City getTransposeCity(const City &city);

            static bool isStronglyConnected(const City &city);

            static CrossroadPtr findConnectedNode(const std::vector<CrossroadPtr> &crossroads);
        };

    }

#endif //CITYMAP_CYCLEFINDER_H
