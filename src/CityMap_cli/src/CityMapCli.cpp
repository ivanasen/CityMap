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
            log.e("Please specify map file path.");
        }

        if (args.size() != 1) {
            log.e("Invalid arguments!");
        }

        try {
            std::shared_ptr<lib::City> city = fileManager.open(args[0]);
            cityManager = CityManager(city);
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
        } catch (std::logic_error &e) {
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
            cityManager.addCrossroad(args[0]);
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
            cityManager.addRoad(args[0], args[1], std::stoi(args[2]));
            log.i("Road added.");
        }
    }

    void CityMapCli::removeRoad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify road start and end.");
        } else if (args.size() != 2) {
            log.e("Invalid arguments!");
        } else {
            try {
                if (cityManager.removeRoad(args[0], args[1])) {
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
                if (cityManager.hasPath(args[0], args[1])) {
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
    }

    void CityMapCli::closeCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
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
    }

    void CityMapCli::openCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
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
    }

    void CityMapCli::hasCycleFrom(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
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
    }

    void CityMapCli::hasEulerCycle(const std::vector<std::string> &args) {
        if (!args.empty()) {
            log.e("Invalid arguments!");
            return;
        }

        lib::Path cycle = cityManager.findEulerCycle();

        if (cycle.getPath().empty()) {
            log.i("No");
        } else {
            log.i("Yes: ");
            getOstream() << cycle;
        }
    }

    void CityMapCli::canReachAllFrom(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
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
    }

    void CityMapCli::findDeadEnds(const std::vector<std::string> &args) {
        if (!args.empty()) {
            log.e("Invalid arguments!");
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
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            if (cityTraveller.changeLocation(args[0])) {
                log.i("Location changed.");
            } else {
                log.e("Crossroad " + args[0] + " doesn't exist.");
            }
        }
    }

    void CityMapCli::showNeighbours(const std::vector<std::string> &args) {
        std::vector<lib::CrossroadPtr> crossroads = cityTraveller.getNeighbours();
        printCrossroads(getOstream(), crossroads);
    }

    void CityMapCli::moveLocation(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            try {
                lib::Path path = cityTraveller.moveLocation(args[0]);
                log.i(path.toString());
            } catch (const std::invalid_argument &e) {
                log.e(e.what());
            }
        }
    }

    void CityMapCli::showClosed(const std::vector<std::string> &args) {
        if (!args.empty()) {
            log.e("Invalid arguments!");
        }

        std::vector<lib::CrossroadPtr> closed = cityManager.findClosedCrossroads();
        printCrossroads(getOstream(), closed);
    }

    void CityMapCli::configureCommands() {
        using namespace std::placeholders;

        std::unordered_map<std::string, std::function<void(const std::vector<std::string>)>> commands;
        commands["open"] = [&](auto args) { open(args); };
        commands["save"] = [&](auto args) { save(args); };
        commands["save_as"] = [&](auto args) { saveAs(args); };
        commands["add"] = [&](auto args) { addCrossroad(args); };
        commands["add_road"] = [&](auto args) { addRoad(args); };
        commands["rm_road"] = [&](auto args) { removeRoad(args); };
        commands["has_path"] = [&](auto args) { hasPath(args); };
        commands["find_paths"] = [&](auto args) { findShortestPaths(args); };
        commands["close"] = [&](auto args) { closeCrossroad(args); };
        commands["open"] = [&](auto args) { openCrossroad(args); };
        commands["has_cycle_from"] = [&](auto args) { hasCycleFrom(args); };
        commands["euler_cycle"] = [&](auto args) { hasEulerCycle(args); };
        commands["reach_all"] = [&](auto args) { canReachAllFrom(args); };
        commands["dead_ends"] = [&](auto args) { findDeadEnds(args); };
        commands["current"] = [&](auto args) { currentLocation(args); };
        commands["neighbours"] = [&](auto args) { showNeighbours(args); };
        commands["change"] = [&](auto args) { changeLocation(args); };
        commands["mv"] = [&](auto args) { moveLocation(args); };
        commands["closed"] = [&](auto args) { showClosed(args); };

        setCommands(commands);
    }
}