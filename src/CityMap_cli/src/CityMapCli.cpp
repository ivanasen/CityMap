#include "CityMapCli.h"
#include <functional>

namespace CityMap::Cli {

    CityMapCli::CityMapCli(std::ostream &ostream, std::istream &istream)
            : Cli(ostream, istream) {
        setQuitMessage("Exiting CityMap…");
        configureCommands();
    }

    void CityMapCli::onExit() {

    }

    void CityMapCli::open(const std::vector<std::string> &args) {
        log.i("open!");
    }

    void CityMapCli::save(const std::vector<std::string> &args) {
        log.i("save!");
    }

    void CityMapCli::saveAs(const std::vector<std::string> &args) {
        log.i("saveAs!");
    }

    void CityMapCli::addCrossroad(const std::vector<std::string> &args) {
        log.i("addCrossroad!");
    }

    void CityMapCli::addRoad(const std::vector<std::string> &args) {
        log.i("addRoad!");
    }

    void CityMapCli::removeCrossroad(const std::vector<std::string> &args) {
        log.i("removeCrossroad!");
    }

    void CityMapCli::removeRoad(const std::vector<std::string> &args) {
        log.i("removeRoad!");
    }

    void CityMapCli::hasPath(const std::vector<std::string> &args) {
        log.i("hasPath!");
    }

    void CityMapCli::findShortestPaths(const std::vector<std::string> &args) {
        log.i("findShortestPaths!");
    }

    void CityMapCli::closeCrossroad(const std::vector<std::string> &args) {
        log.i("closeCrossroad!");
    }

    void CityMapCli::openCrossroad(const std::vector<std::string> &args) {
        log.i("openCrossroad!");
    }

    void CityMapCli::hasCycleFrom(const std::vector<std::string> &args) {
        log.i("hasCycleFrom!");
    }

    void CityMapCli::hasEulerCycle(const std::vector<std::string> &args) {
        log.i("hasEulerCycle!");
    }

    void CityMapCli::canReachAllFrom(const std::vector<std::string> &args) {
        log.i("canReachAllFrom!");
    }

    void CityMapCli::findDeadEnds(const std::vector<std::string> &args) {
        log.i("findDeadEnds!");
    }

    void CityMapCli::configureCommands() {
        using namespace std::placeholders;

        std::unordered_map<std::string, std::function<void(const std::vector<std::string>)>> commands;
        commands["open"] = std::bind(&CityMapCli::open, *this, _1);
        commands["save"] = std::bind(&CityMapCli::save, *this, _1);
        commands["saveAs"] = std::bind(&CityMapCli::saveAs, *this, _1);
        commands["addCrossroad"] = std::bind(&CityMapCli::addCrossroad, *this, _1);
        commands["addRoad"] = std::bind(&CityMapCli::addRoad, *this, _1);
        commands["removeCrossroad"] = std::bind(&CityMapCli::removeCrossroad, *this, _1);
        commands["removeRoad"] = std::bind(&CityMapCli::removeRoad, *this, _1);
        commands["hasPath"] = std::bind(&CityMapCli::hasPath, *this, _1);
        commands["findShortestPaths"] = std::bind(&CityMapCli::findShortestPaths, *this, _1);
        commands["closeCrossroad"] = std::bind(&CityMapCli::closeCrossroad, *this, _1);
        commands["openCrossroad"] = std::bind(&CityMapCli::openCrossroad, *this, _1);
        commands["hasCycleFrom"] = std::bind(&CityMapCli::hasCycleFrom, *this, _1);
        commands["hasEulerCycle"] = std::bind(&CityMapCli::hasEulerCycle, *this, _1);
        commands["canReachAllFrom"] = std::bind(&CityMapCli::canReachAllFrom, *this, _1);
        commands["findDeadEnds"] = std::bind(&CityMapCli::findDeadEnds, *this, _1);

        setCommands(commands);
    }

}