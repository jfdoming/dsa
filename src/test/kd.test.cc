#include "kd.test.h"

#include <iostream>
#include <vector>

#include "test.h"
#include "ds/kd_tree.h"

void kd_test_basic() {
    KDTree<int> tree{5};

    // Test initial state.
    TEST_ASSERT_EQUAL(tree.size(), 0u);
    TEST_ASSERT_EQUAL_Q(tree.find({1, 2, 3, 4, 5}), tree.end());

    // Test insertion.
    tree.insert({1, 2, 3, 4, 5});
    TEST_ASSERT_EQUAL(tree.size(), 1u);
    const auto &it = tree.find({1, 2, 3, 4, 5});
    TEST_ASSERT_NOT_EQUAL(it, tree.end());
    TEST_ASSERT_EQUAL(*it, (Point<int>{1, 2, 3, 4, 5}));

    // Test deletion.
    tree.remove({1, 2, 3, 4, 5});
    TEST_ASSERT_EQUAL(tree.size(), 0u);
    TEST_ASSERT_EQUAL_Q(tree.find({1, 2, 3, 4, 5}), tree.end());
}

void assert_list_matches(const KDTree<int> &tree,
        const std::vector<Point<int>> &list) {
    auto it = tree.begin();
    auto listIt = list.begin();
    while (listIt != list.end()) {
        TEST_ASSERT_NOT_EQUAL(it, tree.end());
        TEST_ASSERT_EQUAL(*it, *listIt);

        ++it;
        ++listIt;
    }

    TEST_ASSERT_EQUAL_Q(it, tree.end());
}

void kd_test_insertion() {
    KDTree<int> tree{5};

    tree.insert({1, 2, 3, 4, 5});
    tree.insert({5, 4, 3, 2, 1});
    tree.insert({3, 2, 1, 2, 3});

    {
        const auto &it = tree.find({1, 2, 3, 4, 5});
        TEST_ASSERT_NOT_EQUAL(it, tree.end());
        TEST_ASSERT_EQUAL(*it, (Point<int>{1, 2, 3, 4, 5}));
    }

    {
        const auto &it = tree.find({5, 4, 3, 2, 1});
        TEST_ASSERT_NOT_EQUAL(it, tree.end());
        TEST_ASSERT_EQUAL(*it, (Point<int>{5, 4, 3, 2, 1}));
    }

    {
        const auto &it = tree.find({5, 4, 3, 2, 1});
        TEST_ASSERT_NOT_EQUAL(it, tree.end());
        TEST_ASSERT_EQUAL(*it, (Point<int>{5, 4, 3, 2, 1}));
    }

    // Test iteration order.
    assert_list_matches(tree, {
            {1, 2, 3, 4, 5},
            {3, 2, 1, 2, 3},
            {5, 4, 3, 2, 1}
            });
}

void kd_test_deletion() {
}

void kd_test() {
    kd_test_basic();
    kd_test_insertion();
    kd_test_deletion();
}
