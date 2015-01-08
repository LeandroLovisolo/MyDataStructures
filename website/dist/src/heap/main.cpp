#include <iostream>
#include <ctime>
#include <algorithm>

#include "js.h"
#include "heap.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Javascript interface                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifdef EMSCRIPTEN

heap h;
string h_output;

extern "C" {
  void EMSCRIPTEN_KEEPALIVE heap_push(int x) {
    h.push(x);
  }

  void EMSCRIPTEN_KEEPALIVE heap_pop() {
    h.pop();
  }

  void EMSCRIPTEN_KEEPALIVE heap_clear() {
    h.clear();
  }

  const char * EMSCRIPTEN_KEEPALIVE heap_print() {
    h_output = h.print();
    return h_output.c_str();
  }
}

////////////////////////////////////////////////////////////////////////////////
// Terminal interface                                                         //
////////////////////////////////////////////////////////////////////////////////

#else

#define NUM_ITEMS_DEFAULT 10

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
    cout << endl
         << "Inserting " << i << ":" << endl
         << "----------" << endl
         << h.print()
         << "----------" << endl << endl;
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

  cout << "Building heap..." << endl;
  heap h = build_heap(items);

  cout << endl << "Popping elements: " << endl;
  while(!h.empty()) {
    cout << h.pop() << " popped.\tIs heap? " << h.is_heap() << endl;
  }

  return 0;
}

#endif
