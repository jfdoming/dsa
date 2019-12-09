#ifndef INTERACTIVE_SHA256_H
#define INTERACTIVE_SHA256_H

#include "cli.h"

class InteractiveSHA256 : public CLI {
    public:
        InteractiveSHA256();
    private:
        void eachRun() override;
        bool eachFailedMatch(std::string input, bool silent) override;
};

#endif
