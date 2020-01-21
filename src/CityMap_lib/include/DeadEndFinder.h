#ifndef CITYMAP_DEADENDFINDER_H
#define CITYMAP_DEADENDFINDER_H

#include <vector>
#include "Road.h"
#include "City.h"

namespace citymap::lib {

    class DeadEndFinder {
    public:
        static std::vector<std::pair<CrossroadPtr, CrossroadPtr>> findDeadEnds(const City &city);
    };

}

#endif //CITYMAP_DEADENDFINDER_H
