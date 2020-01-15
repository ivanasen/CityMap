#include <Files.h>
#include <fstream>
#include <TextMapFormatter.h>
#include <Strings.h>
#include "MapFileManager.h"

namespace citymap::cli {

    bool MapFileManager::areChangesSaved() const {
        return changesSaved;
    }

    bool MapFileManager::isNewFile() const {
        return currentFilePath.empty();
    }

    std::shared_ptr<lib::City> MapFileManager::getCity() const {
        return city;
    }

    std::shared_ptr<lib::City> MapFileManager::createNew() {
        city = std::make_shared<lib::City>();;
        changesSaved = false;
        return city;
    }

    std::shared_ptr<lib::City> MapFileManager::open(const std::string &filePath) {
        if (utils::Files::isDirectory(filePath.c_str())) {
            throw std::invalid_argument("Given path is a directory: \"" + filePath + "\"");
        }

        std::ifstream file(filePath);
        if (file.fail()) {
            throw std::invalid_argument("File doesn't exist or missing read permissions: \"" + filePath + "\"");
        }

        std::string serialized = utils::Strings::convertIstreamToString(file);
        lib::City deserialized = formatter.deserialize(serialized);
        city = std::make_shared<lib::City>(deserialized);

        return city;
    }

    void MapFileManager::save() {
        if (isNewFile()) {
            throw std::logic_error("Current file doesn't exist, so it can't be saved directly.");
        }

        std::ofstream file(currentFilePath, std::ios::trunc);
        std::string serialized = formatter.serialize(*city);
        file << serialized;
        file.close();
        changesSaved = true;
    }

    void MapFileManager::saveAs(const std::string &savePath) {
        currentFilePath = savePath;
        save();
    }

}