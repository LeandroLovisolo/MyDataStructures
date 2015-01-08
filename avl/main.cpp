#include <iostream>
#include <ctime>
#include <algorithm>

#include "js.h"
#include "avl.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Javascript interface                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifdef EMSCRIPTEN

avl a;
string a_output;

extern "C" {
  void EMSCRIPTEN_KEEPALIVE avl_insert(int x) {
    a.insert(x);
  }

  void EMSCRIPTEN_KEEPALIVE avl_remove(int x) {
    a.remove(x);
  }

  void EMSCRIPTEN_KEEPALIVE avl_clear() {
    a = avl();
  }

  const char * EMSCRIPTEN_KEEPALIVE avl_print() {
    a_output = a.print_new();
    return a_output.c_str();
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

bst<> build_bst(const vector<int> &items) {
  bst<> t;
  for(int i : items) {
    t.insert(i);
  }
  return t;
}

avl build_avl(const vector<int> &items) {
  avl t;
  for(int i : items) {
    t.insert(i);
  }
  return t;
}

int main(int argc, char *argv[]) {
  int num_items = (argc == 1 ? NUM_ITEMS_DEFAULT : atoi(argv[1]));

  vector<int> items = random_items(num_items);

  cout << "Items:" << endl;
  for(int i : items) cout << i << " ";
  cout << endl;

  cout << endl << "BST:" << endl;
  bst<> b = build_bst(items);
  cout << b.print();
  cout << "Is BST? " << b.is_bst() << endl;

  cout << endl << "AVL:" << endl;
  avl a = build_avl(items);
  cout << a.print();
  cout << "Is BST? " << a.is_bst() << endl;
  cout << "Is AVL? " << a.is_avl() << endl;

  return 0;
}

#endif
