#include "AssertionException.h"

using namespace std;

AssertionException::AssertionException(const string& errorMessage)
    : errorMessage{errorMessage} {
}

string AssertionException::message() const {
    return "Assertion failed: " + errorMessage;
}
