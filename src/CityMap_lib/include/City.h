#ifndef CITYMAP_CITY_H
#define CITYMAP_CITY_H


#include <unordered_set>
#include <string>
#include "Crossroad.h"

namespace citymap::lib {

    using CrossroadPtr = std::shared_ptr<Crossroad>;

    class City {
    private:
        std::unordered_map<std::string, int> crossroadIndexes;
        std::vector<CrossroadPtr> crossroads;

    public:
        void addCrossroad(const std::string &crossroad);

        void addRoad(const std::string &from, const std::string &to, int weight);

        bool removeRoad(const std::string &from, const std::string &to);

        const std::vector<CrossroadPtr> &getCrossroads() const;

        CrossroadPtr getCrossroadByName(const std::string &name) const;

        CrossroadPtr getCrossroadById(int id) const;
    };

}

#endif //CITYMAP_CITY_H
