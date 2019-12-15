#pragma once

#include <string>

namespace CityMap::Cli {

    class Log {
    public:
        explicit Log(std::ostream &ostream);

        void i(const std::string &s);

        void e(const std::string &s);

    private:
        std::ostream &ostream;
    };

}