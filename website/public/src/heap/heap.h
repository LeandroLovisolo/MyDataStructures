#ifndef __HEAP_H__
#define __HEAP_H__

#include <vector>
#include <string>

#include "../bst/bt.h"

class heap {
public:
  void push(int x);
  int peek();
  int pop();
  void clear();
  int size();
  bool empty();

  std::string print();
  bool is_heap();

private:
  std::vector<int> items;

  int parent(int i);
  int left(int i);
  int right(int i);
  void swap(int i, int j);
  int smallest(int i);
  void heapify(int i);
  bool is_heap_r(int i);
  bt_node* build_node(int i);
};

#endif
