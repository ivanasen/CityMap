#ifndef CITYMAP_TOKEN_H
#define CITYMAP_TOKEN_H

#include <string>
#include "TokenType.h"

namespace CityMap::Serialization {

    class Token {
    private:
        TokenType type;

        std::string value;

    public:
        Token(const TokenType &type, std::string value);

        [[nodiscard]] TokenType getType() const;

        [[nodiscard]] std::string getValue() const;
    };

}

#endif //CITYMAP_TOKEN_H
