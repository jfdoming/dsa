#ifndef SHA_256_CLI_H
#define SHA_256_CLI_H

#include "cli.h"

class SHA256CLI : public CLI {
    public:
        SHA256CLI();
    private:
        void eachRun() override;
};

#endif
