#ifndef TEST_CLI_H
#define TEST_CLI_H

#include <string>
#include <vector>
#include <functional>

#include "cli.h"

class TestCLI : public CLI {
    public:
        TestCLI(const std::string &moduleName,
                const std::function<void(void)> &test = nullptr);
        TestCLI(const std::string &moduleName,
                const std::initializer_list<std::function<void(void)>> &tests);
    private:
        CLI::Status beforeRun(CLI *parent) override;

        std::string moduleName;
        std::vector<std::function<void(void)>> tests;
};

#endif
