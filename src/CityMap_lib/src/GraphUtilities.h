#ifndef CITYMAP_GRAPHUTILITIES_H
#define CITYMAP_GRAPHUTILITIES_H

#include <vector>
#include "City.h"

namespace CityMapLib {
    void dfsUtil(std::vector<bool> &visited, const CrossroadPtr &c);
}

#endif //CITYMAP_GRAPHUTILITIES_H
