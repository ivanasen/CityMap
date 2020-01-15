#include <sys/stat.h>

#include "Files.h"

namespace citymap::utils {

    bool Files::isDirectory(const char *path) {
        struct stat buf{};
        stat(path, &buf);
        return S_ISDIR(buf.st_mode);
    }

}