#include <iostream>
#include <algorithm>
#include "skiplist.h"

using namespace std;

skiplist::skiplist() : head(0), tail(0) {
  head.forward.push_back(&tail);
}

skiplist::~skiplist() {
  node *current = head.forward[0];
  while(current != &tail) {
    node *old = current;
    current = current->forward[0];
    delete old;
  }
}

bool skiplist::find(int value) {
  node *current = &head;
  for(int level = head.level(); level >= 0; level--) {
    while(current->forward[level] != &tail &&
          current->forward[level]->value <= value) {
      current = current->forward[level];
      if(current->value == value) return true;
    }
  }
  return false;
}

void skiplist::insert(int value) {
  vector<node*> update(head.level() + 1);
  node *current = &head;
  for(int level = head.level(); level >= 0; level--) {
    while(current->forward[level] != &tail &&
          current->forward[level]->value <= value) {
      current = current->forward[level];
    }
    update[level] = current;
  }
  if(current->forward[0]->value == value) return;

  int level = randomLevel();
  if(level > head.level()) {
    for(int i = head.level() + 1; i <= level; i++) {
      update.push_back(&head);
      head.forward.push_back(&tail);
    }
  }
  node *new_node = new node(value);
  for(int i = 0; i <= level; i++) {
    new_node->forward.push_back(update[i]->forward[i]);
    update[i]->forward[i] = new_node;
  }
}

void skiplist::remove(int value) {
  vector<node*> update(head.level() + 1);
  node *current = &head;
  for(int level = head.level(); level >= 0; level--) {
    while(current->forward[level] != &tail &&
          current->forward[level]->value < value) {
      current = current->forward[level];
    }
    update[level] = current;
  }
  if(current->forward[0]->value != value) return;

  node *being_removed = current->forward[0];
  for(int level = 0; level <= being_removed->level(); level++) {
    update[level]->forward[level] = being_removed->forward[level];
  }
  delete being_removed;

  while(head.level() > 0 && head.forward.back() == &tail) {
    head.forward.pop_back();
  }
}

void skiplist::clear() {
  while(!empty()) {
    remove(head.forward[0]->value);
  }
}

bool skiplist::empty() {
  return head.forward[0] == &tail;
}

string skiplist::print() {
  string output;
  if(empty()) {
    output = "Empty skip list.";
  } else {
    for(int level = head.level(); level >= 0; level--) {
      node *current = &head, *current_0 = &head;
      while(current != &tail) {
        output += current == &head ?
            "# " : ("--> " + to_string(current->value) + " ");
        current = current->forward[level];
        current_0 = current_0->forward[0];
        while(current_0 != current) {
          output += current_0 == &head ?
            "-" : string(to_string(current_0->value).length() + 5, '-');
          current_0 = current_0->forward[0];
        }
      }
      output += "--> #\n";
    }
  }
  return output;
}

int skiplist::randomLevel() {
  int level = 0;
  while(rand() % 2 == 0) level++;
  return level;
}
