#ifndef CITYMAP_MAPMANAGER_H
#define CITYMAP_MAPMANAGER_H

#include <bits/basic_string.h>
#include <City.h>
#include <DijkstraPathFinder.h>

namespace citymap::cli {

    class MapManager {
    private:
        std::shared_ptr<lib::City> city;
        lib::DijkstraPathFinder pathFinder;

    public:
        explicit MapManager(const std::shared_ptr<lib::City> &city);

        void addCrossroad(const std::string &crossroad);

        void addRoad(const std::string &from, const std::string &to, int weight);

        bool removeRoad(const std::string &from, const std::string &to);

        [[nodiscard]] bool hasPath(const std::string &from, const std::string &to) const;

        [[nodiscard]] std::vector<lib::Path> findShortestPaths(
                const std::string &from,
                const std::string &to,
                int maxPathsCount = 1) const;

        bool setCrossroadClosed(const std::string &crossroad, bool closed);

        [[nodiscard]] bool hasCycleFrom(const std::string &crossroad) const;

        [[nodiscard]] lib::Path findEulerCycle() const;

        [[nodiscard]] bool canReachAllFrom(const std::string &crossroad) const;

        [[nodiscard]] std::vector<std::pair<lib::CrossroadPtr, lib::CrossroadPtr>> findDeadEnds() const;

        [[nodiscard]] std::vector<lib::CrossroadPtr> findClosedCrossroads() const;

        [[nodiscard]] const std::shared_ptr<lib::City> &getCity() const;

    private:
        void requireCrossroadExists(const std::string &crossroad) const;
    };

}

#endif //CITYMAP_MAPMANAGER_H
