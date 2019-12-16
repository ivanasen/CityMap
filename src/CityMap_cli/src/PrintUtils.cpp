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
            ostream << "(" << p.first->getName() << " -> " << p.second->getName() << ")";

            if (p != pairs.back()) {
                ostream << ", ";
            }
        }

        ostream << '\n';
    }
}