#include <iostream>
#include <ctime>
#include <algorithm>

#include "js.h"
#include "skiplist.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Javascript interface                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifdef EMSCRIPTEN

skiplist s;
string output;

extern "C" {
  void EMSCRIPTEN_KEEPALIVE skiplist_insert(int x) {
    s.insert(x);
  }

  void EMSCRIPTEN_KEEPALIVE skiplist_remove(int x) {
    s.remove(x);
  }

  void EMSCRIPTEN_KEEPALIVE skiplist_clear() {
    s.clear();
  }

  const char * EMSCRIPTEN_KEEPALIVE skiplist_print() {
    output = s.print();
    return output.c_str();
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

skiplist build_skiplist(vector<int> &items) {
  skiplist l;
  cout << "Empty skip list:" << endl;
  cout << l.print();

  for(int i : items) {
    cout << endl << "Inserting " << i << ":" << endl;
    l.insert(i);
    cout << l.print();
  }
  return l;
}

void find_items(skiplist &l, vector<int> &items) {
  for(int i : items) {
    cout << "find(" << i << "):\t" << l.find(i) << endl;
  }
}

void remove_items(skiplist &l, vector<int> &items) {
  for(int i : items) {
    cout << endl << "Removing " << i << ":" << endl;
    l.remove(i);
    cout << l.print() << endl;
  }
}

int main(int argc, char *argv[]) {
  int num_items = (argc == 1 ? NUM_ITEMS_DEFAULT : atoi(argv[1]));

  vector<int> items = random_items(num_items);

  cout << "Items:" << endl;
  for(int i : items) cout << i << " ";
  cout << endl;

  cout << endl << "Building skip list..." << endl;
  skiplist l = build_skiplist(items);

  cout << endl << "Finding elements:" << endl;
  find_items(l, items);

  cout << endl << "Removing elements:" << endl;
  remove_items(l, items);

  return 0;
}

#endif
