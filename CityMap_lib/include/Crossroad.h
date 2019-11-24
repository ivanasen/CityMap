#ifndef CITYMAP_CROSSROAD_H
#define CITYMAP_CROSSROAD_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "Road.h"

namespace CityMapLib {

    class Road;

    class Crossroad {
    public:
        typedef std::shared_ptr<Crossroad> CrossroadPtr;

        Crossroad(int id, std::string name);

        void addRoadTo(const CrossroadPtr &crossroad, int weight);

        bool removeRoadTo(const CrossroadPtr &crossroad);

        void setBlocked(bool isBlocked);

        bool isBlocked() const;

        std::string getName() const;

        const std::vector<Road> &getRoads() const;

        int getId() const;

        bool operator==(const Crossroad &other) const;

    private:
        const int id;
        const std::string name;
        std::vector<Road> roads;
        bool blocked = false;
    };

}

#endif //CITYMAP_CROSSROAD_H
