#ifndef DS_CLI_H
#define DS_CLI_H

#include "cli.h"

class DSCLI : public CLI {
    public:
        DSCLI();
    private:
        void eachRun() override;
};

#endif
