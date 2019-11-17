#include "ds.cli.h"

#include <iostream>

#include "test.cli.h"

using namespace std;

DSCLI::DSCLI() : CLI{"ds", {new TestCLI{"ds"}}} {
}

void DSCLI::eachRun() {
    cout << "Enter one of : " << flush;
}
