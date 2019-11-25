#include <utility>

#include "Path.h"

namespace CityMapLib {

    Path::Path(std::vector<CrossroadPtr> path, int distance)
            : path(std::move(path)), distance(distance) {
    }

    const std::vector<CrossroadPtr> &Path::getPath() const {
        return path;
    }

    int Path::getDistance() const {
        return distance;
    }

    Path Path::addToPath(const Road &road) {
        std::vector<CrossroadPtr> newPath(path);
        newPath.push_back(road.getCrossroad().lock());
        return Path(newPath, distance + road.getWeight());
    }

    bool Path::operator==(const Path &other) const {
        return path == other.getPath() && distance == other.getDistance();
    }

}