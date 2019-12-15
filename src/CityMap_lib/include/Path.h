#ifndef CITYMAP_PATH_H
#define CITYMAP_PATH_H

#include <vector>
#include "City.h"
#include "Crossroad.h"

namespace CityMap::Lib {

    class Path {
    private:
        std::vector<CrossroadPtr> path;
        int distance;
    public:
        Path(std::vector<CrossroadPtr> path, int distance);

        Path addToPath(const Road &road);

        [[nodiscard]] const std::vector<CrossroadPtr> &getPath() const;

        [[nodiscard]] int getDistance() const;

        bool operator==(const Path &other) const;

        class DistanceComparator {
        public:
            bool operator()(const Path &left, const Path &right) {
                return left.getDistance() < right.getDistance();
            }
        };
    };

}

#endif //CITYMAP_PATH_H
