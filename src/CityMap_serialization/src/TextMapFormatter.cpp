#include <vector>
#include "City.h"
#include "Token.h"
#include "TextMapFormatter.h"
#include "Strings.h"

namespace citymap::serialization {

    const char TextMapFormatter::LINE_SEPARATOR = '\n';

    const char TextMapFormatter::ELEMENT_SEPARATOR = ' ';

    lib::City TextMapFormatter::deserialize(const std::string &serialized) const {
        std::vector<Token> tokens = tokenize(serialized);

        lib::City city;

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

                        std::string crossroadName = token.getValue();
                        int weight = std::stoi(tokens[i].getValue());

                        if (!city.getCrossroadByName(crossroadName)) {
                            city.addCrossroad(crossroadName);
                        }
                        city.addRoad(currentCrossroad, crossroadName, weight);
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

    std::string TextMapFormatter::serialize(const lib::City &city) const {
        std::string serialized;

        std::vector<lib::CrossroadPtr> crossroads = city.getCrossroads();

        for (const lib::CrossroadPtr &crossroad : crossroads) {
            serialized += crossroad->getName();

            const std::vector<lib::Road> &roads = crossroad->getOutgoingRoads();

            for (const lib::Road &road : roads) {
                serialized += ELEMENT_SEPARATOR;

                lib::CrossroadPtr to = road.getCrossroad().lock();
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

                if (utils::Strings::isInteger(element)) {
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