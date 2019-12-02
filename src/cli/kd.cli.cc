#include "kd.cli.h"

#include <iostream>

#include "test.cli.h"
#include "test/kd.test.h"

using namespace std;

KDCLI::KDCLI() : CLI{"kd",
    {
        new TestCLI{"kd", {
            kd_test_basic,
            kd_test_insertion,
            kd_test_iteration,
            kd_test_deletion
        }}
    }
} {
}

void KDCLI::eachRun() {
    cout << "Enter one of : " << flush;
}
