#ifndef CITYMAP_CITYTRAVELLER_H
#define CITYMAP_CITYTRAVELLER_H


#include <memory>
#include <City.h>
#include "MapManager.h"

namespace citymap::cli {

    class CityTraveller {
    private:
        std::shared_ptr<lib::City> city;
        MapManager mapManager;

        lib::CrossroadPtr currentLocation;

    public:
        explicit CityTraveller(const MapManager &mapManager);

        bool changeLocation(const std::string &location);

        lib::Path moveLocation(const std::string &location);

        [[nodiscard]] lib::CrossroadPtr getCurrentLocation() const;

        [[nodiscard]] std::vector<lib::CrossroadPtr> getNeighbours() const;
    };

}

#endif //CITYMAP_CITYTRAVELLER_H
