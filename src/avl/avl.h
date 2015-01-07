#ifndef __AVL_H__
#define __AVL_H__

#include "../bst/bst.h"

class avl_node : public bst_node_t<avl_node> {
public:
  avl_node(int value, avl_node *parent = nullptr);
  std::string label();
  void update_height();

  int height;
};

class avl : public bst<avl_node> {
public:
  avl_node* insert(int value);
  bool remove(int value);

  bool is_avl();

private:
  void rotate_left(avl_node *node);
  void rotate_right(avl_node *node);
  void rebalance(avl_node *node);
  bool is_avl_r(avl_node *node);
};

#endif
