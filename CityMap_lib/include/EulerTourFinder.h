#ifndef CITYMAP_EULERTOURFINDER_H
#define CITYMAP_EULERTOURFINDER_H

#include <vector>
#include "City.h"

namespace CityMapLib {

    class EulerTourFinder {
    public:
        static bool hasEulerTour(const City &city);

        static std::vector<CrossroadPtr> findEulerTour(const City &city);

    private:
        static City getTransposeCity(const City &city);

        static bool isStronglyConnected(const City &city);

        static void dfsUtil(std::vector<bool> &visited, const CrossroadPtr &c);
    };

}

#endif //CITYMAP_EULERTOURFINDER_H
