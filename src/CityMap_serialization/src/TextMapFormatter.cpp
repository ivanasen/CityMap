#include <iostream>
#include <City.h>
#include <vector>
#include "Token.h"
#include "TextMapFormatter.h"
#include "Strings.h"
#include <algorithm>

namespace CityMap::Serialization {

    const char TextMapFormatter::LINE_SEPARATOR = '\n';

    const char TextMapFormatter::ELEMENT_SEPARATOR = ' ';

    Lib::City TextMapFormatter::deserialize(const std::string &serialized) const {
        std::vector<Token> tokens = tokenize(serialized);

        Lib::City city;

        bool readingNewCrossroad = true;
        std::string currentCrossroad;

        for (size_t i = 0; i < tokens.size(); ++i) {
            Token token = tokens[i];

            switch (token.getType()) {
                case TokenType::ELEMENT:
                case TokenType::NUMBER: {
                    if (readingNewCrossroad) {
                        currentCrossroad = token.getValue();
                        city.addCrossroad(currentCrossroad);
                        readingNewCrossroad = false;
                    } else {
                        if (i == tokens.size() - 1 || tokens[i + 1].getType() != TokenType::NUMBER) {
                            throw std::invalid_argument("Unspecified road weight!");
                        }

                        ++i;

                        int weight = std::stoi(tokens[i].getValue());
                        city.addRoad(currentCrossroad, token.getValue(), weight);
                    }

                    break;
                }
                case TokenType::LINE_SEPARATOR: {
                    readingNewCrossroad = true;
                    break;
                }
            }
        }

        return city;
    }

    std::string TextMapFormatter::serialize(const Lib::City &city) const {
        std::string serialized;

        std::vector<Lib::CrossroadPtr> crossroads = city.getCrossroads();

        for (const Lib::CrossroadPtr &crossroad : crossroads) {
            serialized += crossroad->getName();

            const std::vector<Lib::Road> &roads = crossroad->getOutgoingRoads();

            for (const Lib::Road &road : roads) {
                serialized += ELEMENT_SEPARATOR;

                Lib::CrossroadPtr to = road.getCrossroad().lock();
                serialized += to->getName();
                serialized += ELEMENT_SEPARATOR;
                serialized += std::to_string(road.getWeight());
            }

            serialized += LINE_SEPARATOR;
        }

        return serialized;
    }

    std::vector<Token> TextMapFormatter::tokenize(const std::string &serialized) {
        std::vector<Token> tokens;

        for (size_t i = 0; i < serialized.size(); ++i) {
            char currentChar = serialized[i];

            if (currentChar == LINE_SEPARATOR) {
                tokens.emplace_back(TokenType::LINE_SEPARATOR, std::string(1, LINE_SEPARATOR));
            } else if (!isspace(currentChar)) {
                std::string element = extractNextElement(serialized, i);

                if (Utils::Strings::isInteger(element)) {
                    tokens.emplace_back(TokenType::NUMBER, element);
                } else {
                    tokens.emplace_back(TokenType::ELEMENT, element);
                }
            }
        }

        return tokens;
    }

    std::string TextMapFormatter::extractNextElement(const std::string &serialized, size_t &index) {
        std::string element;

        while (index < serialized.size() && !isspace(serialized[index])) {
            element += serialized[index++];
        }
        --index;

        return element;
    }
}