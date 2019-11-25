#include <utility>

#include "Path.h"

namespace CityMapLib {

    Path::Path(std::vector<std::shared_ptr<Crossroad>> path, int distance)
            : path(std::move(path)), distance(distance) {
    }

    const std::vector<std::shared_ptr<Crossroad>> &Path::getPath() const {
        return path;
    }

    int Path::getDistance() const {
        return distance;
    }

    Path Path::addToPath(const Road &road) {
        std::vector<std::shared_ptr<Crossroad>> newPath(path);
        newPath.push_back(road.getCrossroad().lock());
        return Path(newPath, distance + road.getWeight());
    }

    bool Path::operator==(const Path &other) const {
        return path == other.getPath() && distance == other.getDistance();
    }

}