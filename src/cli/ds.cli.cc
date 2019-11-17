#include "ds.cli.h"

#include <iostream>

#include "test.cli.h"
#include "kd.cli.h"

using namespace std;

DSCLI::DSCLI() : CLI{"ds", {new TestCLI{"ds"}, new KDCLI}} {
}

void DSCLI::eachRun() {
    cout << "Enter one of kd: " << flush;
}
