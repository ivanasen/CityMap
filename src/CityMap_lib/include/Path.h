#ifndef CITYMAP_PATH_H
#define CITYMAP_PATH_H

#include <vector>
#include "City.h"
#include "Crossroad.h"

namespace citymap::lib {

    class Path {
    private:
        static const int DISTANCE_NOT_CALCULATED;

        std::vector<CrossroadPtr> path;
        int distance;
    public:
        explicit Path(std::vector<CrossroadPtr> path);

        Path(std::vector<CrossroadPtr> path, int distance);

        Path addToPath(const Road &road);

        [[nodiscard]] const std::vector<CrossroadPtr> &getPath() const;

        [[nodiscard]] int getDistance() const;

        bool operator==(const Path &other) const;

        [[nodiscard]] std::string toString() const;

        friend std::ostream &operator<<(std::ostream &ostream, const Path &path);

        class DistanceComparator {
        public:
            bool operator()(const Path &left, const Path &right) const;
        };
    };

}

#endif //CITYMAP_PATH_H
