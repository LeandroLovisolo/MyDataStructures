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

void skiplist::print() {
    for(int level = head.level(); level >= 0; level--) {
        node *current = &head, *current_0 = &head;
        while(current != &tail) {
            cout << (current == &head ? "#" : to_string(current->value));
            current = current->forward[level];
            while(current_0 != current) {
                cout << "\t";
                current_0 = current_0->forward[0];
            }
        }
        cout << "#" << endl;
    }
}

int skiplist::randomLevel() {
    int level = 0;
    while(rand() % 2 == 0) level++;
    return level;
}

void heap::push(int x) {
    items.push_back(x);
    int i = items.size() - 1;
    while(i > 0 && items[parent(i)] > items[i]) {
        swap(i, parent(i));
        i = parent(i);
    }
}

int heap::pop() {
    int item = peek();
    swap(0, items.size() - 1);
    items.pop_back();
    if(!empty()) {
        heapify(0);
    }
    return item;
}

int heap::peek() {
    return items[0];
}

int heap::size() {
    return items.size();
}

bool heap::empty() {
    return size() == 0;
}

void heap::print() {
    for(int i : items) {
        cout << i << " ";
    }
    cout << endl;
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