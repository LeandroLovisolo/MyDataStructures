#include <iostream>
#include <ctime>
#include <algorithm>
#include "heap.h"

#define NUM_ITEMS_DEFAULT 10

using namespace std;

vector<int> random_items(int num_items) {
    vector<int> items(num_items);
    for(int i = 0; i < num_items; i++) { 
        items[i] = i + 1;
    }
    srand(time(NULL));
    random_shuffle(items.begin(), items.end());
    return items;
}

heap build_heap(const vector<int> &items) {
    heap h;
    for(int i : items) {
        h.push(i);
        cout << "Inserting " << i << ":\t";
        h.print();
        if(!h.is_heap()) {
            cout << "ERROR: heap property broken." << endl;;
        }
    }
    return h;
}

int main(int argc, char *argv[]) {
    int num_items = (argc == 1 ? NUM_ITEMS_DEFAULT : atoi(argv[1]));

    vector<int> items = random_items(num_items);

    cout << "Items:" << endl;
    for(int i : items) cout << i << " ";
    cout << endl;

    cout << endl << "Building heap..." << endl;
    heap h = build_heap(items);

    cout << endl << "Heap:" << endl;
    h.print();

    cout << endl << "Popping elements: " << endl;
    while(!h.empty()) {
        cout << h.pop() << " popped.\tIs heap? " << h.is_heap() << endl;
    }

    return 0;
}