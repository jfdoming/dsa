#include "TestException.h"

using namespace std;

void TestException::set_message(const string &new_message) {
    message = "An exception occurred while running a test:\n" + new_message;
}

const char *TestException::what() const noexcept {
    return message.c_str();
}
