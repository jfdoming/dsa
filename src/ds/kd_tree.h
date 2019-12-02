#ifndef KD_TREE_H
#define KD_TREE_H

#include <vector>
#include <stack>

template <typename T>
using Point = std::vector<T>;

template <typename T>
class KDTree {
    public:
        template <typename U>
        class Node {
            public:
                Point<U> operator*() const {
                    return p;
                }

                bool operator==(const Node<U> &o) {
                    return p == o.p;
                }

                bool operator==(const Point<U> &o) {
                    return p == o;
                }

                ~Node() {
                    delete left;
                    delete right;
                }
            private:
                Node(Point<U> p) : p{p}, left{nullptr}, right{nullptr} {
                }

                Point<U> p;
                Node<U> *left;
                Node<U> *right;

                friend class KDTree;
        };

        template <typename U>
        class Iterator {
            public:
                bool operator!=(const Iterator<U> &o) const {
                    return o.n != n;
                }
                bool operator==(const Iterator<U> &o) const {
                    return !(*this != o);
                }
                Point<U> operator*() const {
                    return **n;
                }

                Iterator<U> operator++() {
                    n = curr;
                    while (true) {
                        if (curr) {
                            stack.push(curr);
                            curr = n = curr->left;
                        } else {
                            if (stack.empty()) {
                                // We've reached the end.
                                n = nullptr;
                                break;
                            }

                            curr = n = stack.top();
                            stack.pop();
                            curr = curr->right;

                            // Visit the current node.
                            break;
                        }
                    }

                    return *this;
                };
            private:
                Iterator(Node<U> *n) : n{n}, curr{n} {
                }

                Node<U> *n;
                Node<U> *curr;
                std::stack<Node<U> *> stack;

                friend class KDTree;
        };

        template <typename U>
        struct Iterator;

        KDTree(size_t k) : k{k}, s{0}, root{nullptr} {
        }

        ~KDTree() {
            delete root;
        }

        void insert(const Point<T> &p) {
            root = insert_impl(p, root, 0);

            if (root) {
                ++s;
            }
        }

        Node<T> *min_at(Node<T> *n, size_t d) {
            return min_at_impl(n, d, d);
        }

        void remove(const Point<T> &p) {
            if (root) {
                --s;
            }
            root = remove_impl(p, root, 0);
        }

        Iterator<T> find(const Point<T> &p) const {
            return find_impl(p, root, 0);
        }

        Iterator<T> begin() const {
            return ++Iterator<T>{root};
        }

        Iterator<T> end() const {
            return nullptr;
        }

        size_t size() const {
            return s;
        }
    private:
        size_t k;
        size_t s;
        Node<T> *root;

        Node<T> *insert_impl(const Point<T> &p, Node<T> *n, size_t d) {
            if (n == nullptr) {
                return new Node<T>{p};
            }

            size_t i = d % k;
            if (p[i] >= n->p[i]) {
                n->right = insert_impl(p, n->right, d + 1);
            } else {
                n->left = insert_impl(p, n->left, d + 1);
            }

            return n;
        }

        Node<T> *min_at_impl(Node<T> *n, size_t d, size_t cd) {
            if (!n) {
                return nullptr;
            }

            size_t i = cd % k;
            if (i == d) {
                auto *left_min = min_at_impl(n->left, d, cd + 1);
                if (left_min) {
                    return left_min;
                }
                return n;
            }

            auto *left_min = min_at_impl(n->left, d, cd + 1);
            auto *right_min = min_at_impl(n->right, d, cd + 1);
            if (!left_min) {
                return right_min;
            }
            if (!right_min) {
                return left_min;
            }

            return left_min->p[i] < right_min->p[i] ? left_min : right_min;
        }

        Node<T> *remove_impl(const Point<T> &p, Node<T> *n, size_t d) {
            if (!n) {
                return nullptr;
            }

            size_t i = d % k;

            if (*n == p) {
                // Remove this node!
                if (n->right) {
                    auto *newN = min_at(n->right, i);
                    newN->left = nullptr;
                    newN->right = remove_impl(newN->p, n->right, d + 1);
                    return newN;
                } else if (n->left) {
                    auto *newN = min_at(n->left, i);
                    newN->left = nullptr;
                    newN->right = remove_impl(newN->p, n->left, d + 1);
                    return newN;
                } else {
                    return nullptr;
                }
            }

            if (p[i] >= n->p[i]) {
                n->right = remove_impl(p, n->right, d + 1);
            } else {
                n->left = remove_impl(p, n->left, d + 1);
            }
            return n;
        }

        Node<T> *find_impl(const Point<T> &p, Node<T> *n, size_t d) const {
            if (!n) {
                return nullptr;
            }

            if (*n == p) {
                return n;
            }

            size_t i = d % k;
            if (p[i] >= n->p[i]) {
                return find_impl(p, n->right, d + 1);
            } else {
                return find_impl(p, n->left, d + 1);
            }
        }
};

#endif
