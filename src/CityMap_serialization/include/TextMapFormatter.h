#ifndef CITYMAP_TEXTMAPFORMATTER_H
#define CITYMAP_TEXTMAPFORMATTER_H

#include "City.h"
#include "MapFormatter.h"
#include "Token.h"

namespace citymap::serialization {

    class TextMapFormatter : public MapFormatter {
    public:
        static const char LINE_SEPARATOR;
        static const char ELEMENT_SEPARATOR;

        [[nodiscard]] lib::City deserialize(const std::string &serialized) const override;

        [[nodiscard]] std::string serialize(const lib::City &city) const override;

    private:
        static std::vector<Token> tokenize(const std::string &serialized);

        static std::string extractNextElement(const std::string &serialized, size_t &index);
    };

}

#endif //CITYMAP_TEXTMAPFORMATTER_H
