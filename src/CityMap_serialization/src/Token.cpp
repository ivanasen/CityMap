#include "Token.h"

namespace CityMap::Serialization {

    Token::Token(const TokenType &type, std::string value) : type(type), value(std::move(value)) {
    }

    TokenType Token::getType() const {
        return type;
    }

    std::string Token::getValue() const {
        return value;
    }

}