#ifndef TEST_CLI_H
#define TEST_CLI_H

#include <string>
#include <functional>

#include "cli.h"

class TestCLI : public CLI {
    public:
        TestCLI(const std::string &moduleName,
                const std::function<void(void)> &test = nullptr);
    private:
        CLI::Status beforeRun(CLI *parent) override;

        std::string moduleName;
        std::function<void(void)> test;
};

#endif
