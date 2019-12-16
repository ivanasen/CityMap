#ifndef CITYMAP_MAPFORMATTER_H
#define CITYMAP_MAPFORMATTER_H

#include <istream>
#include <string>
#include <City.h>

namespace citymap::serialization {

    class MapFormatter {
    public:
        [[nodiscard]] virtual lib::City deserialize(const std::string &serialized) const = 0;

        [[nodiscard]] virtual std::string serialize(const lib::City &city) const = 0;
    };

}

#endif //CITYMAP_MAPFORMATTER_H
