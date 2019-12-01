#include "AssertionException.h"

using namespace std;

AssertionException::AssertionException(const string& error_message) {
        set_message("Assertion failed: " + error_message);
}
