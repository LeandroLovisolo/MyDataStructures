#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#include <vector>

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
    void print();

private:
    node head, tail;
    int randomLevel();
};


class heap {
public:
    void push(int x);
    int pop();
    int peek();
    int size();
    bool empty();

    void print();
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
};

#endif