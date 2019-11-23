#ifndef CITYMAP_CROSSROAD_H
#define CITYMAP_CROSSROAD_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "Road.h"

typedef std::shared_ptr<Crossroad> CrossroadPtr;

class Crossroad {
public:
    explicit Crossroad(std::string name);

    void addRoadTo(const CrossroadPtr &crossroad, int weight);

    bool removeRoadTo(const CrossroadPtr &crossroad);

    std::string getName() const;

    const std::vector<Road> &getRoads() const;

    bool operator==(const Crossroad &other) const;

private:
    const std::string name;
    std::vector<Road> roads;
};

#endif //CITYMAP_CROSSROAD_H
