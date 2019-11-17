#ifndef TEST_EXCEPTION_H
#define TEST_EXCEPTION_H

#include <exception>
#include <string>

class TestException : public std::exception {
    public:
        const char *what() const throw() final override;
    protected:
        virtual std::string message() const = 0;
};

#endif
