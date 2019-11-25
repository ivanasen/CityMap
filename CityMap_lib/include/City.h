#ifndef CITYMAP_CITY_H
#define CITYMAP_CITY_H


#include <unordered_set>
#include <string>
#include "Crossroad.h"

namespace CityMapLib {

    class City {
    private:
        std::unordered_map<std::string, int> crossroadIndexes;
        std::vector<std::shared_ptr<Crossroad>> crossroads;

    public:
        void addCrossroad(const std::string &crossroad);

        void addRoad(const std::string &from, const std::string &to, int weight);

        bool removeRoad(const std::string &from, const std::string &to);

        const std::vector<std::shared_ptr<Crossroad>> &getCrossroads() const;

        std::shared_ptr<Crossroad> getCrossroadByName(const std::string &name) const;
    };

}

#endif //CITYMAP_CITY_H
