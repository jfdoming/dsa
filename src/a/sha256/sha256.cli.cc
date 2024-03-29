#include "sha256.cli.h"

#include <iostream>

#include "test.cli.h"
#include "interactive_sha256.cli.h"
#include "sha256.test.h"

using namespace std;

SHA256CLI::SHA256CLI() : CLI{"sha256",
    {
        new TestCLI{"sha256", {
            sha256_test
        }},
        new InteractiveSHA256
    }
} {
}

void SHA256CLI::eachRun() {
    cout << "Enter one of i: " << flush;
}
