#include <ostream>
#include <Path.h>

namespace citymap::cli {

    void printPaths(std::ostream &ostream, const std::vector<lib::Path> &paths) {
        int i = 1;
        for (const lib::Path &path : paths) {
            ostream << "Path #" << i << ": " << path;
        }
    }

    void printCrossroadPairs(
            std::ostream &ostream,
            const std::vector<std::pair<lib::CrossroadPtr, lib::CrossroadPtr>> &pairs) {
        for (const auto &p : pairs) {
            ostream << "(" << p.first->toString() << " -> " << p.second->toString() << ")";

            if (p != pairs.back()) {
                ostream << ", ";
            }
        }

        ostream << '\n';
    }

    void printCrossroads(std::ostream &ostream, const std::vector<lib::CrossroadPtr> &crossroads) {
        ostream << "{ ";
        for (const auto &c : crossroads) {
            ostream << c->toString();
            if (c != crossroads.back()) {
                ostream << ", ";
            }
        }
        ostream << " }" << std::endl;
    }
}
