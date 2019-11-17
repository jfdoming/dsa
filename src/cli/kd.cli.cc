#include "kd.cli.h"

#include <iostream>

#include "test.cli.h"
#include "test/kd.test.h"

using namespace std;

KDCLI::KDCLI() : CLI{"kd", {new TestCLI{"kd", kd_test}}} {
}

void KDCLI::eachRun() {
    cout << "Enter one of : " << flush;
}
