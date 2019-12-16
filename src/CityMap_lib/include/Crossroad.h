#ifndef CITYMAP_CROSSROAD_H
#define CITYMAP_CROSSROAD_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "Road.h"

namespace CityMap::Lib {

    class Road;

    class Crossroad {
    public:
        Crossroad(int id, std::string name);

        void addRoadTo(const std::weak_ptr<Crossroad> &crossroad, int weight);

        void addRoadFrom(const std::weak_ptr<Crossroad> &crossroad, int weight);

        bool removeRoadTo(const std::weak_ptr<Crossroad> &crossroad);

        bool removeRoadFrom(const std::weak_ptr<Crossroad> &crossroad);

        void setClosed(bool isClosed);

        [[nodiscard]] bool isClosed() const;

        [[nodiscard]] std::string getName() const;

        [[nodiscard]] const std::vector<Road> &getOutgoingRoads() const;

        [[nodiscard]] const std::vector<Road> &getIncomingRoads() const;

        [[nodiscard]] int getId() const;

        bool operator==(const Crossroad &other) const;

        bool operator!=(const Crossroad &other) const;

    private:
        const int id;
        const std::string name;
        std::vector<Road> outgoingRoads;
        std::vector<Road> incomingRoads;
        bool closed = false;
    };
}

#endif //CITYMAP_CROSSROAD_H
