#include "CityMapCli.h"
#include <functional>
#include <Strings.h>
#include <CycleFinder.h>
#include <DeadEndFinder.h>

namespace CityMap::Cli {

    const int CityMapCli::SHORTEST_PATHS_COUNT = 3;

    CityMapCli::CityMapCli(std::ostream &ostream, std::istream &istream)
            : Cli(ostream, istream), pathFinder(city) {
        setQuitMessage("Exiting CityMap…");
        configureCommands();
    }

    void CityMapCli::open(const std::vector<std::string> &args) {
        // TODO: Implement open
        log.e("Not implemented!");
    }

    void CityMapCli::save(const std::vector<std::string> &args) {
        // TODO: Implement save
        log.e("Not implemented!");
    }

    void CityMapCli::saveAs(const std::vector<std::string> &args) {
        // TODO: Implement saveAs
        log.e("Not implemented!");
    }

    void CityMapCli::addCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad name.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            city.addCrossroad(args[0]);
            log.i("Crossroad added.");
        }
    }

    void CityMapCli::addRoad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify road start, end and weight.");
        } else if (args.size() != 3) {
            log.e("Invalid arguments!");
        } else if (!Utils::Strings::isInteger(args[2])) {
            log.e("Invalid road weight!");
        } else {
            city.addRoad(args[0], args[1], std::stoi(args[2]));
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
            if (city.removeRoad(args[0], args[1])) {
                log.i("Road removed.");
            } else {
                log.i("Road doesn't exist.");
            }
        }
    }

    void CityMapCli::hasPath(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify path start and end.");
        } else if (args.size() != 2) {
            log.e("Invalid arguments!");
        } else if (!city.getCrossroadByName(args[0])) {
            log.e("Crossroad doesn't exist: " + args[0]);
        } else if (!city.getCrossroadByName(args[1])) {
            log.e("Crossroad doesn't exist: " + args[1]);
        } else {
            if (pathFinder.hasPath(args[0], args[1])) {
                log.i("Yes");
            } else {
                log.i("No");
            }
        }
    }

    void CityMapCli::findShortestPaths(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify path start and end.");
        } else if (args.size() != 2) {
            log.e("Invalid arguments!");
        } else {
            std::vector<Lib::Path> paths = pathFinder.findShortestPaths(args[0], args[1], SHORTEST_PATHS_COUNT);
            if (!paths.empty()) {
                log.i("Yes");
            } else {
                log.i("There are not paths between " + args[0] + " and " + args[1]);
            }
        }
    }

    void CityMapCli::closeCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            Lib::CrossroadPtr crossroad = city.getCrossroadByName(args[0]);
            if (!crossroad) {
                log.e("Such crossroad doesn't exist");
            } else if (crossroad->isClosed()) {
                log.i("Crossroad is already closed");
            } else {
                crossroad->setClosed(true);
                log.i("Closed crossroad: " + args[0]);
            }
        }
    }

    void CityMapCli::openCrossroad(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            Lib::CrossroadPtr crossroad = city.getCrossroadByName(args[0]);
            if (!crossroad) {
                log.e("Such crossroad doesn't exist");
            } else if (!crossroad->isClosed()) {
                log.i("Crossroad is already opened");
            } else {
                crossroad->setClosed(false);
                log.i("Opened crossroad: " + args[0]);
            }
        }
    }

    void CityMapCli::hasCycleFrom(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            Lib::CrossroadPtr crossroad = city.getCrossroadByName(args[0]);
            if (!crossroad) {
                log.e("Such crossroad doesn't exist");
            } else {
                if (Lib::CycleFinder::hasCycle(city, args[0])) {
                    log.i("Yes");
                } else {
                    log.i("No");
                }
            }
        }
    }

    void CityMapCli::hasEulerCycle(const std::vector<std::string> &args) {
        if (!args.empty()) {
            log.e("Invalid arguments!");
            return;
        }

        if (!Lib::CycleFinder::hasEulerCycle(city)) {
            log.i("City doesn't have an Euler cycle.");
        } else {
            std::vector<Lib::CrossroadPtr> cycle = Lib::CycleFinder::findEulerCycle(city);
            log.i("Yes:");
            // TODO: Log cycle
        }
    }

    void CityMapCli::canReachAllFrom(const std::vector<std::string> &args) {
        if (args.empty()) {
            log.e("Please specify crossroad.");
        } else if (args.size() != 1) {
            log.e("Invalid arguments!");
        } else {
            Lib::CrossroadPtr crossroad = city.getCrossroadByName(args[0]);
            if (!crossroad) {
                log.e("Such crossroad doesn't exist");
            } else {
                if (pathFinder.hasPathToAll(args[0])) {
                    log.i("Yes");
                } else {
                    log.i("No");
                }
            }
        }
    }

    void CityMapCli::findDeadEnds(const std::vector<std::string> &args) {
        if (!args.empty()) {
            log.e("Invalid arguments!");
            return;
        }

        std::vector<std::pair<Lib::CrossroadPtr, Lib::CrossroadPtr>> deadEnds =
                Lib::DeadEndFinder::findDeadEnds(city);

        if (deadEnds.empty()) {
            log.e("There are no dead-ends in this city");
        } else {
            // TODO: Log dead ends
        }
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
        commands["hasEulerCycle"] = [&](auto args) { hasEulerCycle(args); };
        commands["canReachAllFrom"] = [&](auto args) { canReachAllFrom(args); };
        commands["findDeadEnds"] = [&](auto args) { findDeadEnds(args); };

        setCommands(commands);
    }

}