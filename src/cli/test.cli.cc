#include "test.cli.h"

#include <iostream>

#include "TestException.h"

using namespace std;

TestCLI::TestCLI(const string &moduleName, const function<void(void)> &test)
    : CLI{"test"}, moduleName{moduleName}, test{test} {
    }

CLI::Status TestCLI::beforeRun(CLI *parent) {
    cout << "Running tests for module \"" << moduleName << "\"..." << endl;

    int failures = 0;

    if (parent) {
        parent->forEachChild([&failures](CLI *child) {
                CLI::Status result = child->exec("test");
                if (result.type == CLI::Status::Type::IGNORE && result.code) {
                    failures += result.code;
                }
        });
    }

    if (test) {
        try {
            test();
        } catch (const TestException &e) {
            cerr << e.what() << endl;
            ++failures;
        }
    }

    if (failures) {
        cout << failures << " test" << (failures == 1 ? "" : "s")
             << " failed for module \"" << moduleName << "\"." << endl;
        return {CLI::Status::Type::IGNORE, failures};
    } else {
        cout << "All tests passed for module \"" << moduleName << "\"." << endl;
        return CLI::Status::Type::IGNORE;
    }
}
