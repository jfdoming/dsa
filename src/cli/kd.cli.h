#ifndef KD_CLI_H
#define KD_CLI_H

#include "cli.h"

class KDCLI : public CLI {
    public:
        KDCLI();
    private:
        void eachRun() override;
};

#endif
