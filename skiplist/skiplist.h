#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#include <vector>
#include <string>

class node {
public:
  node(int value) : value(value) {}

  int value;
  std::vector<node*> forward;
  int level() {
    return forward.size() - 1;
  }
};

class skiplist {
public:
  skiplist();
  ~skiplist();
  bool find(int value);
  void insert(int value);
  void remove(int value);
  void clear();
  bool empty();
  std::string print();

private:
  node head, tail;
  int randomLevel();
};

#endif
