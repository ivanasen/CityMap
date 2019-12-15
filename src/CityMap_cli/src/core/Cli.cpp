#include <utility>

#include <iostream>
#include <functional>
#include "Strings.h"
#include "Cli.h"

namespace CityMap::Cli {

    Cli::Cli(std::ostream &ostream, std::istream &istream)
            : Cli(ostream,
                  istream,
                  DEFAULT_CMD_PREFIX(),
                  DEFAULT_QUIT_COMMAND(),
                  DEFAULT_QUIT_MESSAGE()) {
    }

    Cli::Cli(
            std::ostream &ostream,
            std::istream &istream,
            std::string commandPrefix,
            std::string quitCommand,
            std::string quitMessage)
            : ostream(ostream),
              istream(istream),
              log(ostream),
              cmdPrefix(std::move(commandPrefix)),
              quitCmd(std::move(quitCommand)),
              quitMsg(std::move(quitMessage)) {
    }

    void Cli::start() {
        std::string input;
        ostream << cmdPrefix;
        do {
            getline(istream, input);
            input = Utils::Strings::trim(input);
            if (!input.empty() && input != quitCmd) {
                onInput(input);
            }
            ostream << cmdPrefix;
        } while (input != quitCmd);

        onExit();

        ostream << quitMsg << std::endl;
    }

    void Cli::setCommandPrefix(const std::string &prefix) {
        this->cmdPrefix = prefix;
    }

    std::string Cli::getCommandPrefix() {
        return cmdPrefix;
    }

    std::string Cli::DEFAULT_CMD_PREFIX() {
        return "> ";
    }

    std::string Cli::DEFAULT_QUIT_COMMAND() {
        return "exit";
    }

    std::string Cli::DEFAULT_QUIT_MESSAGE() {
        return "Exiting the program...";
    }

    void Cli::setQuitMessage(const std::string &quitMessage) {
        quitMsg = quitMessage;
    }

    std::string Cli::getExitMessage() {
        return quitMsg;
    }

    std::ostream &Cli::getOstream() {
        return ostream;
    }

    std::istream &Cli::getIstream() {
        return istream;
    }

    void Cli::onInput(const std::string &input) {
        std::vector<std::string> separatedInput = separateInput(input);

        if (separatedInput.empty()) {
            return;
        }

        std::string command = separatedInput[0];
        separatedInput.erase(separatedInput.begin());

        if (commands[command]) {
            commands[command](separatedInput);
        } else {
            log.e("Unknown command: " + command);
        }
    }

    std::vector<std::string> Cli::separateInput(const std::string &input) {
        std::string trimmed = Utils::Strings::trim(input);
        std::vector<std::string> separatedInput = Utils::Strings::splitBySpaces(input, 2);
        return separatedInput;
    }

    const std::unordered_map<std::string, std::function<void(const std::vector<std::string>)>> &
    Cli::getCommands() const {
        return commands;
    }

    void Cli::setCommands(
            const std::unordered_map<std::string, std::function<void(const std::vector<std::string>)>> &newCommands) {
        this->commands = newCommands;
    }

    void Cli::onExit() {

    }

}