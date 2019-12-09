#include "a.cli.h"

#include <iostream>

#include "test.cli.h"
#include "a/sha256/sha256.cli.h"

using namespace std;

ACLI::ACLI() : CLI{"a", {new TestCLI{"a"}, new SHA256CLI}} {
}

void ACLI::eachRun() {
    cout << "Enter one of sha256: " << flush;
}
