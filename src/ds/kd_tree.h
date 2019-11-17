#ifndef KD_TREE_H
#define KD_TREE_H

#include <vector>
#include <set>

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

                Iterator<U> operator++() const {
                    return next_impl(n);
                };
            private:
                Iterator(Node<U> *n, Node<U> *parent = nullptr,
                        const std::set<Node<U> *> &visited = {})
                    : n{n}, parent{parent}, visited{visited} {
                }

                Iterator<U> next_impl(Node<U> *current) const {
                    if (current->left) {
                        if (visited.find(current->left) == visited.end()) {
                            visited.insert(current);
                            return {current->left, current, visited};
                        }
                    }
                    if (current->right) {
                        if (visited.find(current->right) == visited.end()) {
                            visited.insert(current);
                            return {current->right, current, visited};
                        }
                    }

                    if (parent) {
                        return next_impl(parent);
                    }
                    return nullptr;
                }

                Node<U> *n;
                Node<U> *parent;
                std::set<Node<U> *> visited;

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

        Node<T> *min_at(Node<T> *n, int d) {
            if (!n) {
                return nullptr;
            }

            auto *left_min = min_at(n->left, d + 1);
            auto *right_min = min_at(n->right, d + 1);
            if (!left_min) {
                return right_min;
            }
            if (!right_min) {
                return left_min;
            }

            size_t i = d % k;
            return left_min->p[i] < right_min->p[i] ? left_min : right_min;
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
            return root;
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
