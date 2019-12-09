#ifndef A_CLI_H
#define A_CLI_H

#include "cli.h"

class ACLI : public CLI {
    public:
        ACLI();
    private:
        void eachRun() override;
};

#endif
