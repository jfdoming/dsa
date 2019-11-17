#ifndef TEST_H
#define TEST_H

#include <iostream>

#include "TestException.h"
#include "AssertionException.h"

#define TEST_ASSERT(cond) if (!(cond)) throw AssertionException{#cond};
#define TEST_ASSERT_EQUAL(lhs, rhs) if (!(lhs == rhs)) throw AssertionException{"Expected "#lhs" to equal "#rhs"."};
#define TEST_ASSERT_NOT_EQUAL(lhs, rhs) if ((lhs == rhs)) throw AssertionException{"Expected "#lhs" to not equal "#rhs"."};
#define TEST_BEGIN() try {
#define TEST_END() } catch (const TestException &e) { std::cerr << e.what() << std::endl; }

#endif
