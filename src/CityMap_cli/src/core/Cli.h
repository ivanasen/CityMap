#pragma once

#include <string>
#include <functional>
#include <fstream>
#include "Log.h"

namespace CityMap::Cli {

    class Cli {
    private:
        std::string cmdPrefix;
        std::string quitCmd;
        std::string quitMsg;

        std::ostream &ostream;
        std::istream &istream;

        std::unordered_map<std::string, std::function<void(const std::vector<std::string>)>> commands;

    public:
        Cli(std::ostream &ostream,
            std::istream &istream);

        Cli(std::ostream &ostream,
            std::istream &istream,
            std::string commandPrefix,
            std::string quitCommand,
            std::string quitMessage);

        virtual void start();

    protected:
        Log log;

        void onInput(const std::string &input);

        virtual void onExit();

        void setCommandPrefix(const std::string &prefix);

        void setQuitMessage(const std::string &quitMessage);

        std::string getCommandPrefix();

        std::string getExitMessage();

        static std::string DEFAULT_CMD_PREFIX();

        static std::string DEFAULT_QUIT_COMMAND();

        static std::string DEFAULT_QUIT_MESSAGE();

        std::ostream &getOstream();

        std::istream &getIstream();

    public:
        const std::unordered_map<std::string, std::function<void(const std::vector<std::string>)>> &getCommands() const;

        void setCommands(
                const std::unordered_map<std::string, std::function<void(const std::vector<std::string>)>> &newCommands);

    private:
        static std::vector<std::string> separateInput(const std::string &input);
    };


}