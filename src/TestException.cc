#include "TestException.h"

const char *TestException::what() const throw() {
    return ("An exception occurred while running a test:\n" + message()).c_str();
}
