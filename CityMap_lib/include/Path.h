#ifndef CITYMAP_PATH_H
#define CITYMAP_PATH_H

#include <vector>
#include "Crossroad.h"

namespace CityMapLib {

    class Path {
    private:
        std::vector<std::shared_ptr<Crossroad>> path;
        int distance;
    public:
        Path(std::vector<std::shared_ptr<Crossroad>> path, int distance);

        Path addToPath(const Road &road);

        [[nodiscard]] const std::vector<std::shared_ptr<Crossroad>> &getPath() const;

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
