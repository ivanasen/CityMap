#ifndef CITYMAP_CITYMAPCLI_H
#define CITYMAP_CITYMAPCLI_H

#include <vector>
#include <City.h>
#include <DijkstraPathFinder.h>
#include "core/Cli.h"

namespace CityMap::Cli {

    // TODO: Add project bonus commands: location, change, neighbours, move, closed,
    class CityMapCli : public Cli {
    private:
        static const int SHORTEST_PATHS_COUNT;

        Lib::City city;
        Lib::DijkstraPathFinder pathFinder;

    public:
        CityMapCli(std::ostream &ostream, std::istream &istream);

    private:
        void configureCommands();

        void open(const std::vector<std::string> &args);

        void save(const std::vector<std::string> &args);

        void saveAs(const std::vector<std::string> &args);

        void addCrossroad(const std::vector<std::string> &args);

        void addRoad(const std::vector<std::string> &args);

        void removeCrossroad(const std::vector<std::string> &args);

        void removeRoad(const std::vector<std::string> &args);

        void hasPath(const std::vector<std::string> &args);

        void findShortestPaths(const std::vector<std::string> &args);

        void closeCrossroad(const std::vector<std::string> &args);

        void openCrossroad(const std::vector<std::string> &args);

        void hasCycleFrom(const std::vector<std::string> &args);

        void hasEulerCycle(const std::vector<std::string> &args);

        void canReachAllFrom(const std::vector<std::string> &args);

        void findDeadEnds(const std::vector<std::string> &args);
    };

}

#endif //CITYMAP_CITYMAPCLI_H
