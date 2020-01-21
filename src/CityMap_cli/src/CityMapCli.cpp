#include "CityMapCli.h"
#include <functional>
#include "PrintUtils.h"
#include <Strings.h>

namespace citymap::cli {

    const int CityMapCli::SHORTEST_PATHS_COUNT = 3;

    CityMapCli::CityMapCli(std::ostream &ostream, std::istream &istream)
            : cityManager(fileManager.getCity()),
              Cli(ostream, istream),
              cityTraveller(fileManager.getCity()) {
        setQuitMessage("Exiting CityMap…");
        configureCommands();
    }

    void CityMapCli::open(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify map file path");
            return;
        }

        if (!requireArgumentsCount(args, 1)) {
            return;
        }

        std::string mapFile = args[0];

        try {
            std::shared_ptr<lib::City> city = fileManager.open(mapFile);
            cityManager = CityManager(city);
            cityTraveller = lib::CityTraveller(city);
            log.i("Map " + mapFile + " opened");
        } catch (std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::save(const std::vector<std::string> &args) {
        if (!requireArgumentsCount(args, 0)) {
            return;
        }

        try {
            fileManager.save();
            log.i("Map saved to " + fileManager.getCurrentFilePath());
        } catch (std::logic_error &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::saveAs(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify map file path");
            return;
        }

        if (!requireArgumentsCount(args, 1)) {
            return;
        }

        try {
            fileManager.saveAs(args[0]);
            log.i("Map saved to " + fileManager.getCurrentFilePath());
        } catch (std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::addCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad name");
            return;
        }

        if (!requireArgumentsCount(args, 1)) {
            return;
        }

        try {
            cityManager.addCrossroad(args[0]);
            log.i("Crossroad added");
        } catch (const std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::addRoad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify road start, end and weight");
            return;
        }

        if (!requireArgumentsCount(args, 3)) {
            return;
        }

        if (!utils::Strings::isInteger(args[2])) {
            log.e("Invalid road weight!");
            return;
        }

        cityManager.addRoad(args[0], args[1], std::stoi(args[2]));
        log.i("Road added");
    }

    void CityMapCli::removeRoad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify road start and end");
            return;
        }

        if (!requireArgumentsCount(args, 2)) {
            return;
        }

        try {
            if (cityManager.removeRoad(args[0], args[1])) {
                log.i("Road removed");
            } else {
                log.i("Road doesn't exist");
            }
        } catch (const std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::hasPath(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify path start and end");
            return;
        }

        if (!requireArgumentsCount(args, 2)) {
            return;
        }

        try {
            if (cityManager.hasPath(args[0], args[1])) {
                log.i("Yes");
            } else {
                log.i("No");
            }
        } catch (const std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::findShortestPaths(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify path start and end");
            return;
        }

        if (!requireArgumentsCount(args, 2)) {
            return;
        }

        try {
            std::vector<lib::Path> paths =
                    cityManager.findShortestPaths(args[0], args[1], SHORTEST_PATHS_COUNT);

            if (!paths.empty()) {
                printPaths(getOstream(), paths);
            } else {
                log.i("There are not paths between " + args[0] + " and " + args[1]);
            }
        } catch (const std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::closeCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad");
            return;
        }

        if (!requireArgumentsCount(args, 1)) {
            return;
        }

        try {
            if (cityManager.setCrossroadClosed(args[0], true)) {
                log.i("Closed crossroad: " + args[0]);
            } else {
                log.i("Crossroad is already closed");
            }
        } catch (const std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::openCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
            return;
        }

        if (!requireArgumentsCount(args, 1)) {
            return;
        }

        try {
            if (cityManager.setCrossroadClosed(args[0], false)) {
                log.i("Opened crossroad: " + args[0]);
            } else {
                log.i("Crossroad is already opened");
            }
        } catch (const std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::hasCycleFrom(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
            return;
        }

        if (!requireArgumentsCount(args, 1)) {
            return;
        }

        try {
            if (cityManager.hasCycleFrom(args[0])) {
                log.i("Yes");
            } else {
                log.i("No");
            }
        } catch (std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::hasEulerCycle(const std::vector<std::string> &args) {
        if (!requireArgumentsCount(args, 0)) {
            return;
        }

        try {
            lib::Path cycle = cityManager.findEulerCycle();
            log.i("Yes: ");
            getOstream() << cycle;
        } catch (const std::invalid_argument &e) {
            log.i("No");
        }
    }

    void CityMapCli::canReachAllFrom(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
            return;
        }

        if (!requireArgumentsCount(args, 1)) {
            return;
        }

        try {
            if (cityManager.canReachAllFrom(args[0])) {
                log.i("Yes");
            } else {
                log.i("No");
            }
        } catch (const std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::findDeadEnds(const std::vector<std::string> &args) {
        if (!requireArgumentsCount(args, 0)) {
            return;
        }

        std::vector<std::pair<lib::CrossroadPtr, lib::CrossroadPtr>> deadEnds =
                cityManager.findDeadEnds();

        if (deadEnds.empty()) {
            log.i("There are no dead-ends in this city");
        } else {
            printCrossroadPairs(getOstream(), deadEnds);
        }
    }

    void CityMapCli::currentLocation(const std::vector<std::string> &args) {
        if (!requireArgumentsCount(args, 0)) {
            return;
        }

        lib::CrossroadPtr currentLocation = cityTraveller.getCurrentLocation();
        if (currentLocation) {
            log.i(cityTraveller.getCurrentLocation()->getName());
        } else {
            log.e("Current city is still empty.");
        }
    }

    void CityMapCli::changeLocation(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
            return;
        }

        if (!requireArgumentsCount(args, 1)) {
            return;
        }

        if (cityTraveller.changeLocation(args[0])) {
            log.i("Location changed.");
        } else {
            log.e("Crossroad " + args[0] + " doesn't exist.");
        }
    }

    void CityMapCli::showNeighbours(const std::vector<std::string> &args) {
        if (!requireArgumentsCount(args, 0)) {
            return;
        }

        std::vector<lib::CrossroadPtr> crossroads = cityTraveller.getNeighbours();
        printCrossroads(getOstream(), crossroads);
    }

    void CityMapCli::moveLocation(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
            return;
        }

        if (!requireArgumentsCount(args, 1)) {
            return;
        }

        try {
            lib::Path path = cityTraveller.moveLocation(args[0]);
            log.i(path.toString());
        } catch (const std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::showClosed(const std::vector<std::string> &args) {
        if (!requireArgumentsCount(args, 0)) {
            return;
        }

        std::vector<lib::CrossroadPtr> closed = cityManager.findClosedCrossroads();
        printCrossroads(getOstream(), closed);
    }

    void CityMapCli::configureCommands() {
        using namespace std::placeholders;

        std::unordered_map<std::string, std::function<void(const std::vector<std::string>)>> commands;
        commands["open_map"] = [&](auto args) { open(args); };
        commands["save"] = [&](auto args) { save(args); };
        commands["save_as"] = [&](auto args) { saveAs(args); };
        commands["add"] = [&](auto args) { addCrossroad(args); };
        commands["add_road"] = [&](auto args) { addRoad(args); };
        commands["rm_road"] = [&](auto args) { removeRoad(args); };
        commands["has_path"] = [&](auto args) { hasPath(args); };
        commands["show_paths"] = [&](auto args) { findShortestPaths(args); };
        commands["close"] = [&](auto args) { closeCrossroad(args); };
        commands["open"] = [&](auto args) { openCrossroad(args); };
        commands["cycle_from"] = [&](auto args) { hasCycleFrom(args); };
        commands["tour"] = [&](auto args) { hasEulerCycle(args); };
        commands["reach_all"] = [&](auto args) { canReachAllFrom(args); };
        commands["dead_ends"] = [&](auto args) { findDeadEnds(args); };
        commands["loc"] = [&](auto args) { currentLocation(args); };
        commands["nbs"] = [&](auto args) { showNeighbours(args); };
        commands["change"] = [&](auto args) { changeLocation(args); };
        commands["move"] = [&](auto args) { moveLocation(args); };
        commands["closed"] = [&](auto args) { showClosed(args); };

        setCommands(commands);
    }

    bool CityMapCli::requireArgumentsCount(const std::vector<std::string> &args, int count) {
        if (args.size() != count) {
            log.e("Invalid arguments!");
            return false;
        }
        return true;
    }
}