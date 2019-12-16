#pragma once

namespace citymap::utils {

    class Files {
    public:
        static bool isFile(const char *path);

        static bool isDirectory(const char *path);
    };

}