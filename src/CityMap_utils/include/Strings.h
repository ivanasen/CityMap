#pragma once

#include <string>
#include <vector>
#include <unordered_set>

namespace citymap::utils {

    class Strings {
    public:
        static void ltrim(std::string &string);

        static void rtrim(std::string &string);

        static std::string trim(std::string string);

        static std::vector<std::string> splitBySpaces(const std::string &string, int maxSplitAmount = -1);

        static std::vector<std::string> split(const std::string &string, char separator);

        static bool isInteger(const std::string &s);

        static std::string escape(const std::string &s);

    private:
        static const std::unordered_set<char> ESCAPE_CHARS;

    };

}