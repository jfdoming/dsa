#ifndef MAIN_CLI_H
#define MAIN_CLI_H

#include "cli.h"

class MainCLI : public CLI {
    public:
        MainCLI();
    private:
        CLI::Status beforeRun() override;
        void eachRun() override;
        void afterRun() override;
};

#endif
