#include "Token.h"

namespace citymap::serialization {

    Token::Token(const TokenType &type, std::string value) : type(type), value(std::move(value)) {
    }

    TokenType Token::getType() const {
        return type;
    }

    std::string Token::getValue() const {
        return value;
    }

}