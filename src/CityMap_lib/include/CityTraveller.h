#ifndef CITYMAP_CITYTRAVELLER_H
#define CITYMAP_CITYTRAVELLER_H


#include <memory>
#include <City.h>
#include "DijkstraPathFinder.h"

namespace citymap::lib {

    class CityTraveller {
    private:
        static const int LOCATION_ID_DEFAULT = 0;

        std::shared_ptr<City> city;
        DijkstraPathFinder pathFinder;
        int currentLocationId = LOCATION_ID_DEFAULT;

    public:
        explicit CityTraveller(const std::shared_ptr<City> &city);

        bool changeLocation(const std::string &location);

        Path moveLocation(const std::string &location);

        [[nodiscard]] CrossroadPtr getCurrentLocation() const;

        [[nodiscard]] std::vector<CrossroadPtr> getNeighbours() const;
    };

}

#endif //CITYMAP_CITYTRAVELLER_H
