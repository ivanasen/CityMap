#include <utility>
#include <iostream>

#include "Path.h"

namespace citymap::lib {

    const int Path::DISTANCE_NOT_CALCULATED = -1;

    Path::Path(std::vector<CrossroadPtr> path, int distance)
            : path(std::move(path)), distance(distance) {
    }

    Path::Path(std::vector<CrossroadPtr> path)
            : path(std::move(path)), distance(DISTANCE_NOT_CALCULATED) {
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

    std::ostream &operator<<(std::ostream &ostream, const Path &path) {
        ostream << path.toString() << std::endl;
        return ostream;
    }

    std::string Path::toString() const {
        std::string result;
        for (const CrossroadPtr &c : path) {
            result += c->toString();
            if (c != path.back()) {
                result += " -> ";
            }
        }
        return result;
    }

}