#include "CityMapCli.h"
#include <functional>
#include <Strings.h>

namespace citymap::cli {

    const int CityMapCli::SHORTEST_PATHS_COUNT = 3;

    CityMapCli::CityMapCli(std::ostream &ostream, std::istream &istream)
            : mapManager(fileManager.getCity()), Cli(ostream, istream) {
        setQuitMessage("Exiting CityMap…");
        configureCommands();
    }

    void CityMapCli::open(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify map file path.");
        }

        if (args.size() != 1) {
            log.e("Invalid arguments!");
        }

        try {
            lib::City &city = fileManager.open(args[0]);
            mapManager.setCity(city);
        } catch (std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::save(const std::vector<std::string> &args) {
        if (!args.empty()) {
            log.e("Invalid arguments!");
        }

        try {
            fileManager.save();
        } catch (std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::saveAs(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify map file path.");
        }

        if (args.size() != 1) {
            log.e("Invalid arguments!");
        }

        try {
            fileManager.saveAs(args[0]);
        } catch (std::invalid_argument &e) {
            log.e(e.what());
        }
    }

    void CityMapCli::addCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad name.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            mapManager.addCrossroad(args[0]);
            log.i("Crossroad added.");
        }
    }

    void CityMapCli::addRoad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify road start, end and weight.");
        } else if (args.size() != 3) {
            log.e("Invalid arguments!");
        } else if (!utils::Strings::isInteger(args[2])) {
            log.e("Invalid road weight!");
        } else {
            mapManager.addRoad(args[0], args[1], std::stoi(args[2]));
            log.i("Road added.");
        }
    }

    void CityMapCli::removeCrossroad(const std::vector<std::string> &args) {
        // TODO: Implement removeCrossroad
        log.e("Not implemented!");
    }

    void CityMapCli::removeRoad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify road start and end.");
        } else if (args.size() != 2) {
            log.e("Invalid arguments!");
        } else {
            try {
                if (mapManager.removeRoad(args[0], args[1])) {
                    log.i("Road removed.");
                } else {
                    log.i("Road doesn't exist.");
                }
            } catch (const std::invalid_argument &e) {
                log.e(e.what());
            }
        }
    }

    void CityMapCli::hasPath(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify path start and end.");
        } else if (args.size() != 2) {
            log.e("Invalid arguments!");
        } else {
            try {
                if (mapManager.hasPath(args[0], args[1])) {
                    log.i("Yes");
                } else {
                    log.i("No");
                }
            } catch (const std::invalid_argument &e) {
                log.e(e.what());
            }
        }
    }

    void CityMapCli::findShortestPaths(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify path start and end.");
        } else if (args.size() != 2) {
            log.e("Invalid arguments!");
        } else {
            try {
                std::vector<lib::Path> paths =
                        mapManager.findShortestPaths(args[0], args[1], SHORTEST_PATHS_COUNT);

                if (!paths.empty()) {
                    // TODO: Log paths
                } else {
                    log.i("There are not paths between " + args[0] + " and " + args[1]);
                }
            } catch (const std::invalid_argument &e) {
                log.e(e.what());
            }
        }
    }

    void CityMapCli::closeCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            try {
                if (mapManager.setCrossroadClosed(args[0], true)) {
                    log.i("Closed crossroad: " + args[0]);
                } else {
                    log.i("Crossroad is already closed");
                }
            } catch (const std::invalid_argument &e) {
                log.e(e.what());
            }
        }
    }

    void CityMapCli::openCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            try {
                if (mapManager.setCrossroadClosed(args[0], true)) {
                    log.i("Opened crossroad: " + args[0]);
                } else {
                    log.i("Crossroad is already opened");
                }
            } catch (const std::invalid_argument &e) {
                log.e(e.what());
            }
        }
    }

    void CityMapCli::hasCycleFrom(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            try {
                if (mapManager.hasCycleFrom(args[0])) {
                    log.i("Yes");
                } else {
                    log.i("No");
                }
            } catch (std::invalid_argument &e) {
                log.e(e.what());
            }
        }
    }

    void CityMapCli::hasEulerCycle(const std::vector<std::string> &args) {
        if (!args.empty()) {
            log.e("Invalid arguments!");
            return;
        }

        std::vector<lib::CrossroadPtr> cycle = mapManager.findEulerCycle();

        if (cycle.empty()) {
            log.i("No");
        } else {
            log.i("Yes: ");
            // TODO: Log Euler cycle
        }
    }

    void CityMapCli::canReachAllFrom(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            try {
                if (mapManager.canReachAllFrom(args[0])) {
                    log.i("Yes");
                } else {
                    log.i("No");
                }
            } catch (const std::invalid_argument &e) {
                log.e(e.what());
            }

        }
    }

    void CityMapCli::findDeadEnds(const std::vector<std::string> &args) {
        if (!args.empty()) {
            log.e("Invalid arguments!");
            return;
        }

        std::vector<std::pair<lib::CrossroadPtr, lib::CrossroadPtr>> deadEnds =
                mapManager.findDeadEnds();

        if (deadEnds.empty()) {
            log.i("There are no dead-ends in this city");
        } else {
            // TODO: Log dead ends
        }
    }

    void CityMapCli::currentLocation(const std::vector<std::string> &args) {
        // TODO: Implement currentLocation
        log.e("Not implemented!");
    }

    void CityMapCli::changeLocation(const std::vector<std::string> &args) {
        // TODO: Implement changeLocation
        log.e("Not implemented!");
    }

    void CityMapCli::showNeighbours(const std::vector<std::string> &args) {
        // TODO: Implement showNeighbours
        log.e("Not implemented!");
    }

    void CityMapCli::moveLocation(const std::vector<std::string> &args) {
        // TODO: Implement moveLocation
        log.e("Not implemented!");
    }

    void CityMapCli::showClosed(const std::vector<std::string> &args) {
        // TODO: Implement showClosed
        log.e("Not implemented!");
    }

    void CityMapCli::configureCommands() {
        using namespace std::placeholders;

        std::unordered_map<std::string, std::function<void(const std::vector<std::string>)>> commands;
        commands["open"] = [&](auto args) { open(args); };
        commands["save"] = [&](auto args) { save(args); };
        commands["saveAs"] = [&](auto args) { saveAs(args); };
        commands["addCrossroad"] = [&](auto args) { addCrossroad(args); };
        commands["addRoad"] = [&](auto args) { addRoad(args); };
        commands["removeCrossroad"] = [&](auto args) { removeCrossroad(args); };
        commands["removeRoad"] = [&](auto args) { removeRoad(args); };
        commands["hasPath"] = [&](auto args) { hasPath(args); };
        commands["findShortestPaths"] = [&](auto args) { findShortestPaths(args); };
        commands["closeCrossroad"] = [&](auto args) { closeCrossroad(args); };
        commands["openCrossroad"] = [&](auto args) { openCrossroad(args); };
        commands["hasCycleFrom"] = [&](auto args) { hasCycleFrom(args); };
        commands["findEulerCycle"] = [&](auto args) { hasEulerCycle(args); };
        commands["canReachAllFrom"] = [&](auto args) { canReachAllFrom(args); };
        commands["findDeadEnds"] = [&](auto args) { findDeadEnds(args); };
        commands["currentLocation"] = [&](auto args) { currentLocation(args); };
        commands["showNeighbours"] = [&](auto args) { showNeighbours(args); };
        commands["changeLocation"] = [&](auto args) { changeLocation(args); };
        commands["moveLocation"] = [&](auto args) { moveLocation(args); };
        commands["showClosed"] = [&](auto args) { showClosed(args); };

        setCommands(commands);
    }

}