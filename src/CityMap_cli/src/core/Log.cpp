#include <iostream>
#include "Log.h"

namespace CityMap::Cli {

    Log::Log(std::ostream &ostream) : ostream(ostream) {
    }

    void Log::i(const std::string &s) {
        ostream << s << std::endl;
    }

    void Log::e(const std::string &s) {
        ostream << s << std::endl;
    }

}