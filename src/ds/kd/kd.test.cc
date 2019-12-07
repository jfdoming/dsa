#include "kd.test.h"

#include <iostream>
#include <vector>

#include "test.h"
#include "ds/kd/kd_tree.h"

using namespace std;

void assert_list_matches(KDTree<int>::Iterator<int> it,
        const KDTree<int>::Iterator<int> &end,
        const std::vector<Point<int>> &list) {
    auto listIt = list.begin();
    while (listIt != list.end()) {
        TEST_ASSERT_NOT_EQUAL_Q(it, end);
        TEST_ASSERT_EQUAL(*it, *listIt);

        ++it;
        ++listIt;
    }

    TEST_ASSERT_EQUAL_Q(it, end);
}

void kd_test_basic() {
    KDTree<int> tree{5};

    // Test initial state.
    TEST_ASSERT_EQUAL(tree.size(), 0u);
    TEST_ASSERT_EQUAL_Q(tree.find({1, 2, 3, 4, 5}), tree.end());

    // Test insertion.
    tree.insert({1, 2, 3, 4, 5});
    TEST_ASSERT_EQUAL(tree.size(), 1u);
    const auto &it = tree.find({1, 2, 3, 4, 5});
    TEST_ASSERT_NOT_EQUAL_Q(it, tree.end());
    TEST_ASSERT_EQUAL(*it, (Point<int>{1, 2, 3, 4, 5}));

    // Test deletion.
    tree.remove({1, 2, 3, 4, 5});
    TEST_ASSERT_EQUAL(tree.size(), 0u);
    TEST_ASSERT_EQUAL_Q(tree.find({1, 2, 3, 4, 5}), tree.end());
}

void kd_test_insertion() {
    KDTree<int> tree{5};

    tree.insert({1, 2, 3, 4, 5});
    tree.insert({5, 4, 3, 2, 1});
    tree.insert({3, 2, 1, 2, 3});

    {
        const auto &it = tree.find({1, 2, 3, 4, 5});
        TEST_ASSERT_NOT_EQUAL_Q(it, tree.end());
        TEST_ASSERT_EQUAL((Point<int>{1, 2, 3, 4, 5}), *it);
    }

    {
        const auto &it = tree.find({5, 4, 3, 2, 1});
        TEST_ASSERT_NOT_EQUAL_Q(it, tree.end());
        TEST_ASSERT_EQUAL((Point<int>{5, 4, 3, 2, 1}), *it);
    }

    {
        const auto &it = tree.find({5, 4, 3, 2, 1});
        TEST_ASSERT_NOT_EQUAL_Q(it, tree.end());
        TEST_ASSERT_EQUAL((Point<int>{5, 4, 3, 2, 1}), *it);
    }

    // Test iteration order.
    assert_list_matches(tree.begin(), tree.end(), {
            {1, 2, 3, 4, 5},
            {3, 2, 1, 2, 3},
            {5, 4, 3, 2, 1}
            });
}

void kd_test_iteration() {
    KDTree<int> tree{3};

    tree.insert({1, 2, 3});
    tree.insert({5, 4, 3});
    tree.insert({3, 2, 1});
    tree.insert({5, 4, 4});
    tree.insert({0, 5, 1});
    tree.insert({3, 9, 2});
    tree.insert({0, 5, -9});

    assert_list_matches(tree.find({0, 5, 1}), tree.end(), {
            {0, 5, 1},
            {0, 5, -9},
            {1, 2, 3},
            {3, 2, 1},
            {5, 4, 3},
            {3, 9, 2},
            {5, 4, 4}
            });
    assert_list_matches(tree.find({0, 5, -9}), tree.end(), {
            {0, 5, -9},
            {1, 2, 3},
            {3, 2, 1},
            {5, 4, 3},
            {3, 9, 2},
            {5, 4, 4}
            });
    assert_list_matches(tree.find({1, 2, 3}), tree.end(), {
            {1, 2, 3},
            {3, 2, 1},
            {5, 4, 3},
            {3, 9, 2},
            {5, 4, 4}
            });
    assert_list_matches(tree.find({3, 2, 1}), tree.end(), {
            {3, 2, 1},
            {5, 4, 3},
            {3, 9, 2},
            {5, 4, 4}
            });
    assert_list_matches(tree.find({5, 4, 3}), tree.end(), {
            {5, 4, 3},
            {3, 9, 2},
            {5, 4, 4}
            });
    assert_list_matches(tree.find({3, 9, 2}), tree.end(), {
            {3, 9, 2},
            {5, 4, 4}
            });
    assert_list_matches(tree.find({5, 4, 4}), tree.end(), {
            {5, 4, 4}
            });
}

void kd_test_deletion() {
}
