#include "kd.test.h"

#include <iostream>

#include "test.h"
#include "ds/kd_tree.h"

void kd_test_basic() {
    KDTree<int> tree{5};

    // Test initial state.
    TEST_ASSERT_EQUAL(tree.size(), 0);
    TEST_ASSERT_EQUAL(tree.find({1, 2, 3, 4, 5}), tree.end());

    // Test insertion.
    tree.insert({1, 2, 3, 4, 5});
    TEST_ASSERT_EQUAL(tree.size(), 1);
    const auto &it = tree.find({1, 2, 3, 4, 5});
    TEST_ASSERT_NOT_EQUAL(it, tree.end());
    TEST_ASSERT_EQUAL(*it, (Point<int>{1, 2, 3, 4, 5}));

    // Test deletion.
    tree.remove({1, 2, 3, 4, 5});
    TEST_ASSERT_EQUAL(tree.size(), 0);
    TEST_ASSERT_EQUAL(tree.find({1, 2, 3, 4, 5}), tree.end());
}

void kd_test_insertion() {
    KDTree<int> tree{5};

    tree.insert({1, 2, 3, 4, 5});
    tree.insert({5, 4, 3, 2, 1});
    tree.insert({3, 2, 1, 2, 3});
}

void kd_test_deletion() {
}

void kd_test() {
    kd_test_basic();
    kd_test_insertion();
    kd_test_deletion();
}
