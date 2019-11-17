#ifndef ASSERTION_EXCEPTION_H
#define ASSERTION_EXCEPTION_H

#include <string>

#include "TestException.h"

class AssertionException : public TestException {
    public:
        AssertionException(const std::string &errorMessage);
    protected:
        std::string message() const override;
    private:
        std::string errorMessage;
};

#endif
