#ifndef CITYMAP_MAPFILEMANAGER_H
#define CITYMAP_MAPFILEMANAGER_H

#include <City.h>
#include "TextMapFormatter.h"

namespace citymap::cli {

    class MapFileManager {
    private:
        bool changesSaved = false;
        std::string currentFilePath;
        lib::City city;
        serialization::TextMapFormatter formatter;

    public:
        lib::City &createNew();

        lib::City &open(const std::string &filePath);

        bool isNewFile() const;

        void save();

        void saveAs(const std::string &savePath);

        [[nodiscard]] bool areChangesSaved() const;

        lib::City &getCity();
    };

}

#endif //CITYMAP_MAPFILEMANAGER_H
