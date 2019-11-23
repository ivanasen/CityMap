#ifndef CITYMAP_CITY_H
#define CITYMAP_CITY_H


#include <unordered_set>
#include <string>
#include "Crossroad.h"

class City {
private:
    std::unordered_map<std::string, CrossroadPtr> crossroads;

public:
    void addCrossroad(const std::string &crossroad);

    void addRoad(const std::string &from, const std::string &to, int weight);

    unsigned long removeRoad(const std::string &from, const std::string &to);

    bool hasRoadBetween(const std::string &from, const std::string &to) const;

private:
    static void throwInvalidCrossroad(const std::string &crossroad);
};


#endif //CITYMAP_CITY_H
