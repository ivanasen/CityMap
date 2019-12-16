#ifndef CITYMAP_PRINTUTILS_H
#define CITYMAP_PRINTUTILS_H

namespace citymap::cli {

    void printPaths(std::ostream &ostream, const std::vector<lib::Path> &paths);

    void printCrossroadPairs(
            std::ostream &ostream,
            const std::vector<std::pair<lib::CrossroadPtr, lib::CrossroadPtr>> &pairs);
}

#endif //CITYMAP_PRINTUTILS_H
