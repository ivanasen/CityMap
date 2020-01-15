#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Strings.h"

namespace citymap::utils {

    const std::unordered_set<char> Strings::ESCAPE_CHARS = { //NOLINT
            '"', '\\', '\n', '\t'
    };

    void Strings::ltrim(std::string &string) {
        std::string::iterator endTrimPosition = string.begin();

        while (std::isspace(*endTrimPosition)) {
            endTrimPosition++;
        }

        string.erase(string.begin(), endTrimPosition);
    }

    void Strings::rtrim(std::string &string) {
        std::string::iterator endTrimPosition = string.end() - 1;
        while (std::isspace(*endTrimPosition)) {
            endTrimPosition--;
        }
        if (endTrimPosition < string.end()) {
            string.erase(endTrimPosition + 1, string.end());
        }
    }

    std::string Strings::trim(std::string string) {
        ltrim(string);
        rtrim(string);
        return string;
    }

    std::vector<std::string> Strings::splitBySpaces(const std::string &string, int maxSplitAmount) {
        int splitAmount = 0;
        std::vector<std::string> separated;
        auto iterator = string.begin();

        while (iterator != string.end()) {
            if (std::isspace(*iterator)) {
                iterator++;
            } else {
                std::string newElement;

                if (splitAmount == maxSplitAmount) {
                    while (iterator != string.end()) {
                        newElement.push_back(*(iterator++));
                    }
                } else {
                    while (iterator != string.end() && !std::isspace(*iterator)) {
                        newElement.push_back(*(iterator++));
                    }
                }

                separated.push_back(newElement);
                splitAmount++;
            }
        }

        return separated;
    }

    std::vector<std::string> Strings::split(const std::string &string, char separator) {
        std::vector<std::string> separated;
        auto iterator = string.begin();

        while (iterator != string.end()) {
            if (*iterator == separator) {
                iterator++;
            } else {
                std::string newElement;
                while (iterator != string.end() && *iterator != separator) {
                    newElement.push_back(*iterator++);
                }
                separated.push_back(newElement);
            }
        }

        return separated;
    }

    bool Strings::isInteger(const std::string &s) {
        std::string trimmed = trim(s);

        for (char c : trimmed) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return !trimmed.empty();
    }

    std::string Strings::escape(const std::string &s) {
        std::string escaped;

        for (char c : s) {
            if (ESCAPE_CHARS.count(c)) {
                escaped += "\\";

                if (c == '\n') {
                    escaped += 'n';
                } else if (c == '\t') {
                    escaped += 't';
                } else {
                    escaped += c;
                }
            } else {
                escaped += c;
            }
        }

        return escaped;
    }

    std::string Strings::convertIstreamToString(std::istream &istream) {
        std::ostringstream outputStream;
        outputStream << istream.rdbuf();
        return outputStream.str();
    }

}