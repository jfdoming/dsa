#include "cli.h"

#include <iostream>

using namespace std;

CLI::Status::Status(CLI::Status::Type type) : type{type}, code{0} {
}

CLI::Status::Status(CLI::Status::Type type, int code)
    : type{type}, code{code} {
    }

CLI::Status::operator int() const {
    return code;
}

CLI::CLI(string key) : key{key}, children{} {
}

CLI::CLI(string key, std::vector<CLI *> children) : key{key}, children{children} {
}

CLI::~CLI() {
    for (CLI *cli : children) {
        delete cli;
    }
}

void CLI::forEachChild(const std::function<void(CLI *)> &fn) {
    for (CLI *child : children) {
        fn(child);
    }
}

CLI::Status CLI::beforeRun() {
    return CLI::Status::Type::OKAY;
}

CLI::Status CLI::beforeRun(CLI *parent) {
    return beforeRun();
}

void CLI::afterRun() {
}

void CLI::eachRun() {
}

bool CLI::eachFailedMatch(string input, bool silent) {
    if (!silent) {
        cout << "No match." << endl;
    }
    return true;
}

bool isEmpty(string input) {
    for (char c : input) {
        if (c != ' ' && c != '\n' && c != '\t') {
            return false;
        }
    }
    return true;
}

CLI::Status CLI::eachInput(string input) {
    if (isEmpty(input)) {
        return CLI::Status::Type::IGNORE;
    }
    if (input == "e" || input == "x" || input == "q"
            || input == "exit" || input == "quit") {
        return CLI::Status::Type::EXIT;
    }
    return CLI::Status::Type::OKAY;
}

CLI::Status CLI::exec(string input, bool silent) {
    bool failedMatch = true;
    CLI::Status result = CLI::Status::Type::OKAY;
    for (CLI *cli : children) {
        if (input == cli->key) {
            result = cli->run(this);
            failedMatch = false;
            break;
        }
    }

    if (failedMatch && !eachFailedMatch(input, silent)) {
        return CLI::Status::Type::EXIT;
    }
    return result;
}

CLI::Status CLI::run(CLI *parent) {
    CLI::Status result = beforeRun(parent);
    if (result.type == CLI::Status::Type::IGNORE
            || result.type == CLI::Status::Type::EXIT) {
        return result;
    }

    string input = "";
    while (true) {
        result = CLI::Status::Type::OKAY;

        eachRun();
        if (!getline(cin, input)) {
            cin.clear();
            cin.ignore();
            break;
        }

        result = eachInput(input);
        if (result.type == CLI::Status::Type::IGNORE) {
            continue;
        }
        if (result.type == CLI::Status::Type::EXIT) {
            break;
        }

        result = exec(input, false);

        if (result.type == CLI::Status::Type::EXIT) {
            break;
        }
    }

    afterRun();

    if (result.type == CLI::Status::Type::EXIT && result == 0) {
        return CLI::Status::Type::OKAY;
    }
    return result;
}
