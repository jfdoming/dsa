#include "interactive_sha256.cli.h"

#include <iostream>

#include "sha256.h"

using namespace std;

InteractiveSHA256::InteractiveSHA256() : CLI{"i"} {
}

void InteractiveSHA256::eachRun() {
    cout << "> " << flush;
}

bool InteractiveSHA256::eachFailedMatch(string input, bool silent) {
    if (silent) {
        return false;
    }

    cout << "Hashed value: " << sha256(input) << endl;
    return true;
}
