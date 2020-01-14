#ifndef CITYMAP_PRINTUTILS_H
#define CITYMAP_PRINTUTILS_H

namespace citymap::cli {

    void printPaths(std::ostream &ostream, const std::vector<lib::Path> &paths);

    void printPath(std::ostream &ostream, const lib::Path &path);

    void printCrossroadPairs(
            std::ostream &ostream,
            const std::vector<std::pair<lib::CrossroadPtr, lib::CrossroadPtr>> &pairs);

    void printCrossroads(std::ostream &ostream, const std::vector<lib::CrossroadPtr> &crossroads);
}

#endif //CITYMAP_PRINTUTILS_H
