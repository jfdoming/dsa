#ifndef TEST_EXCEPTION_H
#define TEST_EXCEPTION_H

#include <exception>
#include <string>

class TestException : public std::exception {
    public:
        const char *what() const noexcept final override;
    protected:
        void set_message(const std::string &new_message);
        std::string message;
};

#endif
