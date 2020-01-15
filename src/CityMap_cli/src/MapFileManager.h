#ifndef CITYMAP_MAPFILEMANAGER_H
#define CITYMAP_MAPFILEMANAGER_H

#include <City.h>
#include "TextMapFormatter.h"

namespace citymap::cli {

    class MapFileManager {
    private:
        bool changesSaved = false;
        std::string currentFilePath;
        std::shared_ptr<lib::City> city = std::make_shared<lib::City>();
        serialization::TextMapFormatter formatter;

    public:
        std::shared_ptr<lib::City> createNew();

        std::shared_ptr<lib::City> open(const std::string &filePath);

        [[nodiscard]] bool isNewFile() const;

        void save();

        void saveAs(const std::string &savePath);

        [[nodiscard]] bool areChangesSaved() const;

        [[nodiscard]] std::shared_ptr<lib::City> getCity() const;

        [[nodiscard]] const std::string &getCurrentFilePath() const;
    };

}

#endif //CITYMAP_MAPFILEMANAGER_H
