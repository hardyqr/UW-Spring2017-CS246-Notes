#include <iostream>
using namespace std;

template<typename T>
class Bintree {
  struct Node {
    T data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
    Node *parent;

    //Utility
    void updateParents() {
      if (left) left->parent = this;
      if (right) right->parent = this;
    }

    //For iterator
    Node *findLeftmostRightDescendent() {
      if (!right) return nullptr;
      return right->findLeftmostDescendent();
    }

    Node *findLeftmostDescendent() {
      Node *temp = this;
      Node *prev = this;
      while (temp == temp->left.get()) {
        prev = temp;
      }
      return prev;
    }

    //For iterator
    Node *findLeftmostRightAncestor() {
      Node *temp = this;
      while (temp->parent) {
        if (temp->parent->left.get() == this) {
          temp = temp->parent;
        } else {
          return temp;
        }
      }
      return nullptr;
    }

    Node(T data, Node *parent):data{data}, left{nullptr}, right{nullptr}, parent{parent} {}
    Node(const Node &other):data{other.data}, left{other.left? make_unique<Node>(*other.left) : unique_ptr<Node>()}, right{other.right? make_unique<Node>(*other.right) : unique_ptr<Node>()}, parent{nullptr} {
      updateParents();
    }
    Node(Node &&other):data{std::move(other.data)}, left{std::move(other.left)}, right{std::move(other.right)}, parent{nullptr} {
      updateParents();
    }
    Node &operator=(const Node &other) {
      Node temp = other;
      std::swap(data,temp.data);
      std::swap(parent,temp.parent);
      left.swap(temp.left);
      right.swap(temp.right);
      return *this;
    }
    Node &operator=(Node &&other) {
      if (this == &other) return *this; //Shouldn't happen unless user abuses std::move
      data = std::move(other.data);
      left = std::move(other.left);
      right = std::move(other.right);
      parent = nullptr;
      updateParents();
      return *this;
    }
  };

  unique_ptr<Node> root;

  //C++-style iterator. If you want an AbstractIterator-style iterator, this should
  //extend AbstractIterator
  class iterator {
    explicit iterator(Node *posn):posn{posn} {}

    bool operator==(const iterator &other) { return posn == other.posn; }
    bool operator!=(const iterator &other) { return posn != other.posn; }
    T operator*() { return posn->data; }
    iterator &operator++() {
      Node *temp = posn->findLeftmostRightDescendent();
      if (!temp) {
        temp = posn->findLeftmostRightAncestor();
      }
      posn = temp;
      return *this;
    }
  };

  iterator begin() {
    if (!root) return end();
    return iterator(root->findLeftmostDescendent());
  }
  iterator end() { return iterator(nullptr); }

  Bintree():root{nullptr} {}
  Bintree(const Bintree<T> &other):root{other.root ? make_unique<Node>(*other.root) : unique_ptr<Node>()} {}
  Bintree(Bintree<T> &&other):root{std::move(other.root)} {}
  Bintree<T> &operator=(const Bintree<T> &other) {
    Bintree<T> temp = other;
    root.swap(temp.root);
    return *this;
  }
  Bintree<T> &operator=(Bintree<T> &&other) {
    root.swap(other.root);
    return *this;
  }
};
