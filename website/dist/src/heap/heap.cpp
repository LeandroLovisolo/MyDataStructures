#include <iostream>
#include <climits>

#include "heap.h"

using namespace std;

void heap::push(int x) {
  items.push_back(x);
  int i = items.size() - 1;
  while(i > 0 && items[parent(i)] > items[i]) {
    swap(i, parent(i));
    i = parent(i);
  }
}

int heap::peek() {
  return items[0];
}

int heap::pop() {
  int item;
  if(empty()) {
    item = INT_MIN;
  } else {
    item = peek();
    swap(0, items.size() - 1);
    items.pop_back();
    if(!empty()) {
      heapify(0);
    }
  }
  return item;
}

void heap::clear() {
  while(!empty()) {
    pop();
  }
}

int heap::size() {
  return items.size();
}

bool heap::empty() {
  return size() == 0;
}

string heap::print() {
  string output;
  if(empty()) {
    output = "Empty heap.";
  } else {
    output += "Underlying array:\n";
    for(int i : items) {
      output += to_string(i) + " ";
    }
    output += "\n\n";

    bt<> t(build_node(0));
    output += t.print();
  }
  return output;
}

bt_node* heap::build_node(int i) {
  if(i >= size()) {
    return nullptr;
  } else {
    bt_node *node = new bt_node(items[i]);
    node->left = build_node(left(i));
    node->right = build_node(right(i));
    return node;
  }
}

bool heap::is_heap() {
  return is_heap_r(0);
}

bool heap::is_heap_r(int i) {
  if(i >= items.size()) return true;
  return i == smallest(i) &&
         is_heap_r(left(i)) &&
         is_heap_r(right(i));
}

int heap::parent(int i) {
  return (i + 1) / 2 - 1;
}

int heap::left(int i) {
  return 2 * (i + 1) - 1;
}

int heap::right(int i) {
  return 2 * (i + 1) + 1 - 1;
}

void heap::swap(int i, int j) {
  int temp = items[i];
  items[i] = items[j];
  items[j] = temp;
}

int heap::smallest(int i) {
  int smallest = i;
  if(left(i) < items.size() && items[left(i)] < items[smallest]) {
    smallest = left(i);
  }
  if(right(i) < items.size() && items[right(i)] < items[smallest]) {
    smallest = right(i);
  }
  return smallest;
}

void heap::heapify(int i) {
  int j = smallest(i);
  if(i != j) {
    swap(i, j);
    heapify(j);
  }
}
