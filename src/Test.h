#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <sstream>
#include <vector>

#include "TestException.h"
#include "AssertionException.h"

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    out << "(";

    bool first = true;
    for (auto t : v) {
        if (first) {
            first = false;
        } else {
            out << ",";
        }
        out << t;
    }
    out << ")";
    return out;
}

void _log_prefix(std::ostringstream &oss, const char *file, int line) {
    oss << "\t" << "at " << file << ":" << line << ": ";
}

template <typename T, typename U>
void test_assert_equal(T t, U u, const char *file, int line, const char *arg) {
    if (!(t == u)) {
        std::ostringstream oss;
        oss << "Expected " << t << " but got " << u << " instead." << std::endl;
        _log_prefix(oss, file, line);
        oss << "TEST_ASSERT_EQUAL(" << arg << ");" << std::endl;
        throw AssertionException{oss.str()};
    }
}

template <typename T, typename U>
void test_assert_equal_q(T t, U u, const char *file, int line, const char *tString, const char *uString) {
    if (!(t == u)) {
        std::ostringstream oss{"Expected "};
        oss << tString << " to equal " << uString << ".";
        _log_prefix(oss, file, line);
        oss << "TEST_ASSERT_EQUAL_Q(" << tString << ", " << uString << ");" << std::endl;
        throw AssertionException{oss.str()};
    }
}
#define TEST_ASSERT_EQUAL(lhs, rhs) test_assert_equal(lhs, rhs, __FILE__, __LINE__, #lhs" == "#rhs);
#define TEST_ASSERT_EQUAL_Q(lhs, rhs) test_assert_equal_q(lhs, rhs, __FILE__, __LINE__, #lhs, #rhs);
#define TEST_ASSERT_NOT_EQUAL(lhs, rhs) if ((lhs == rhs)) throw AssertionException{"Expected "#lhs" to not equal "#rhs"."};
#define TEST_ASSERT(cond) test_assert(cond, #cond);
#define TEST_BEGIN() try {
#define TEST_END() } catch (const TestException &e) { std::cerr << e.what() << std::endl; }

#endif
