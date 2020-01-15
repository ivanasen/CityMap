#include <ostream>
#include <Path.h>

namespace citymap::cli {

    void printPaths(std::ostream &ostream, const std::vector<lib::Path> &paths) {
        int i = 1;
        for (const lib::Path &path : paths) {
            ostream << "Path #" << i++ << ": " << path;
        }
    }

    void printCrossroadPairs(
            std::ostream &ostream,
            const std::vector<std::pair<lib::CrossroadPtr, lib::CrossroadPtr>> &pairs) {
        for (int i = 0; i < pairs.size(); ++i) {
            ostream << "("
                    << pairs[i].first->toString()
                    << " -> "
                    << pairs[i].second->toString()
                    << ")";
            if (i < pairs.size() - 1) {
                ostream << ", ";
            }
        }
        ostream << '\n';
    }

    void printCrossroads(std::ostream &ostream, const std::vector<lib::CrossroadPtr> &crossroads) {
        ostream << "{ ";
        for (int i = 0; i < crossroads.size(); ++i) {
            ostream << crossroads[i]->toString();
            if (i < crossroads.size() - 1) {
                ostream << ", ";
            }
        }
        ostream << " }" << std::endl;
    }
}
