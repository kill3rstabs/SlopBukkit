/* Chris Miller (imperator@pax-imperia.com), CS124
 * Copyright (C) 2014 Chris Miller.  Aw richts pitten by.
 * Academic endorsement.  This code is not licensed for commercial use.
 * 20140509, Chapter 20 Some random assignment from professor
 */

#include <iostream>
#include <utility>
#include <array>
using namespace std;

template<class T>
class binary_tree {
  struct node {
    T data;
    node * left, * right;
    node(T t, node * l = NULL, node * r = NULL) : data(t), left(l), right(r) { }
    ~node() { delete left; delete right; }
  };
  node * root;
  void insert_r(node * &clay, node * &kebab) {
    if (!clay) {
      clay = kebab;
    } else if (kebab->data < clay->data) {
      insert_r(clay->left, kebab);
    } else {
      insert_r(clay->right, kebab);
    }
  }
  void pretty_print_r(ostream& os, node * clay) const {
    if (clay->left) { pretty_print_r(os, clay->left); }
    os << clay->data << ", ";
    if (clay->right) { pretty_print_r(os, clay->right); }
  }
  void pretty_print_leaves_r(ostream& os, node * clay) const {
    if (clay->left) { pretty_print_leaves_r(os, clay->left); }
    if (!clay->left || !clay->right) { os << clay->data << ", "; }
    if (clay->right) { pretty_print_leaves_r(os, clay->right); }
  }
  size_t count_r(node * clay) const {
    if (clay) {
      return 1 + count_r(clay->left) + count_r(clay->right);
    } else {
      return 0;
    }
  }
  size_t leaf_count_r(node * clay) const {
    if (clay) {
      if (clay->left || clay->right) {
        return leaf_count_r(clay->left) + leaf_count_r(clay->right);
      } else {
        return 1; // is of being leaf!
      }
    } else {
      return 0;
    }
  }
  T min_r(node * clay) const {
    if (clay) {
      if (clay->left) { return min_r(clay->left); }
      else { return clay->data; }
    } else {
      return (T)NULL; // NOT PRODUCTIONABLE!
    }
  }
public:
  binary_tree() : root(NULL) { }
  ~binary_tree() { if (root) { delete root; } }
  void insert(T t) {
    node * n = new node(t);
    insert_r(root, n);
  }
  size_t count() const {
    return count_r(root);
  }
  size_t leaf_count() const {
    return leaf_count_r(root);
  }
  T min() const {
    return min_r(root);
  }
  void pretty_print(ostream& os) const {
    os << "{ ";
    if (root) { pretty_print_r(os, root); }
    os << "}" << endl;
  }
  void pretty_print_leaves(ostream& os) const {
    os << "{ ";
    if (root) { pretty_print_leaves_r(os, root); }
    os << "}" << endl;
  }
};

int main(int argc, char *argv[]) {
  array<int, 11> kebabs1{ {12, 7, 9, 10, 22, 24, 30, 18, 3, 14, 20} };
  binary_tree<int> t1;
  cout << "empty tree of " << t1.leaf_count()
       << " leaves: "; t1.pretty_print(cout);
  for (auto& kebab: kebabs1) { t1.insert(kebab); }
  cout  << "filled tree of " << t1.count()
        << " elements and " << t1.leaf_count()
        << " leaves with smallest value of " << t1.min()
        << ": "; t1.pretty_print(cout);
  cout  << " and leaves: "; t1.pretty_print_leaves(cout);
  
  array<int, 10> kebabs2{ {1, 3, 5, 7, 9, 2, 4, 6, 8, 10} };
  binary_tree<int> t2;
  for (auto& kebab: kebabs2) { t2.insert(kebab); }

  cout  << "filled tree of " << t2.count()
        << " elements and " << t2.leaf_count()
        << " leaves with smallest value of " << t2.min()
        << ": "; t2.pretty_print(cout);
  cout  << " and leaves: "; t2.pretty_print_leaves(cout);
  
  return 0;
}