#ifndef CITYMAP_DEADENDFINDER_H
#define CITYMAP_DEADENDFINDER_H

#include <vector>
#include "Road.h"
#include "City.h"

namespace CityMap::Lib {

    class DeadEndFinder {
    public:
        static std::vector<std::pair<CrossroadPtr, CrossroadPtr>> findDeadEnds(const City &city);

    private:
        static void findDeadEndsFrom(
                int start,
                std::vector<std::pair<CrossroadPtr, CrossroadPtr>> &deadEnds,
                std::vector<bool> &visited,
                const std::vector<CrossroadPtr> &crossroads);
    };

}

#endif //CITYMAP_DEADENDFINDER_H
