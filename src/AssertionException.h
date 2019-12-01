#ifndef ASSERTION_EXCEPTION_H
#define ASSERTION_EXCEPTION_H

#include <string>

#include "TestException.h"

class AssertionException : public TestException {
    public:
        AssertionException(const std::string &error_message);
};

#endif
