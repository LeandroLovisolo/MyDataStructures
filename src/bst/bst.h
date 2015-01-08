#ifndef __BST_H__
#define __BST_H__

#include "bt.h"

class bst_node : public bt_node_t<bst_node> {
public:
  bst_node(int value, bst_node *parent = nullptr) : bt_node_t(value, parent) {}
};

template<typename node_t = bst_node>
class bst : public bt<node_t> {
public:
  node_t* find(int value);
  node_t* insert(int value);
  bool remove(int value);

  bool is_bst();

protected:
  void transplant(node_t *n, node_t *m);

private:
  bool is_bst_r(node_t *node);
};

template<typename node_t>
node_t* bst<node_t>::find(int value) {
  node_t *current = this->root;
  while(current != nullptr) {
    if(current->value == value) return current;
    if(value < current->value) current = current->left;
    else current = current->right;
  }
  return nullptr;
}

template<typename node_t>
node_t* bst<node_t>::insert(int value) {
  if(this->root == nullptr) {
    return this->root = new node_t(value);
  } else {
    node_t *parent = this->root;
    while(true) {
      if(value == parent->value) return nullptr;

      node_t *next;
      if(value < parent->value) next = parent->left;
      else next = parent->right;

      if(next == nullptr) break;
      parent = next;
    };
    if(value < parent->value) return parent->left = new node_t(value, parent);
    else return parent->right = new node_t(value, parent);
  }
}

template<typename node_t>
bool bst<node_t>::remove(int value) {
  node_t *node = find(value);
  if(node == nullptr) return false;

  if(node->left == nullptr) {
    transplant(node, node->right);
  } else if(node->right == nullptr) {
    transplant(node, node->left);
  } else {
    node_t *successor = node->right;
    while(successor->left != nullptr) successor = successor->left;
    if(successor->parent != node) {
      transplant(successor, successor->right);
      successor->right = node->right;
      successor->right->parent = successor;
    }
    transplant(node, successor);
    successor->left = node->left;
    successor->left->parent = successor;
  }

  node->left = nullptr;
  node->right = nullptr;
  delete node;

  return true;
}

template<typename node_t>
void bst<node_t>::transplant(node_t *n, node_t *m) {
  if(n->parent == nullptr) {
    this->root = m;
  } else if(n->parent->left == n) {
    n->parent->left = m;
  } else {
    n->parent->right = m;
  }
  if(m != nullptr) {
    m->parent = n->parent;
  }
}

template<typename node_t>
bool bst<node_t>::is_bst() {
  return is_bst_r(this->root);
}

template<typename node_t>
bool bst<node_t>::is_bst_r(node_t *node) {
  if(node == nullptr) return true;
  bool left_ok = node->left == nullptr ||
                 (node->left->value < node->value && is_bst_r(node->left));
  if(!left_ok) return false;
  bool right_ok = node->right == nullptr ||
                  (node->right->value > node->value && is_bst_r(node->right));
  return right_ok;
}

#endif
