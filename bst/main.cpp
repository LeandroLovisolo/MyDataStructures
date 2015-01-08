#include <iostream>
#include <ctime>
#include <algorithm>

#include "js.h"
#include "bst.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Javascript interface                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifdef EMSCRIPTEN

bst<> b;
string bst_output;

extern "C" {
  void EMSCRIPTEN_KEEPALIVE bst_insert(int x) {
    b.insert(x);
  }

  void EMSCRIPTEN_KEEPALIVE bst_remove(int x) {
    b.remove(x);
  }

  void EMSCRIPTEN_KEEPALIVE bst_clear() {
    b = bst<>();
  }

  const char * EMSCRIPTEN_KEEPALIVE bst_print() {
    bst_output = b.print();
    return bst_output.c_str();
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

string center_between(string s, int width, int left, int right);

void assertEqual(string name, string actual, string expected) {
  if(actual == expected) {
    cout << "TEST CASE " << name << " OK." << endl;
  } else {
    cout << "TEST CASE " << name << " FAILED." << endl
         << "  Actual:   '" << actual   << "'" << endl
         << "  Expected: '" << expected << "'" << endl;
  }
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


  cout << endl
       << "New print" << endl
       << "---------" << endl << endl;

  bst<> t;
  // cout << "Empty:" << endl;
  // cout << t.print_new() << endl << endl;
  //
  // for(int i = 10; i <= 30; i+=10) {
  //   t.insert(i);
  //   cout << "After inserting " << i << ":" << endl;
  //   cout << t.print() << endl;
  //   cout << t.print_new() << endl;
  // }
  //
  // t.insert(15);
  // cout << "After inserting " << 15 << ":" << endl;
  // cout << t.print() << endl;
  // cout << t.print_new() << endl;

  for(int x : vector<int> { 4, 2, 1, 3, 6, 5, 7, 100, 9, 8, 11000000}) {
    t.insert(x);
  }

  cout << t.print() << endl;
  cout << t.print_new() << endl;


  // assertEqual("1",  center_between("",      0, 0, 0), "");
  // assertEqual("2",  center_between("a",     1, 0, 0), "a");
  // assertEqual("3",  center_between("a",     2, 0, 1), "a ");
  // assertEqual("4",  center_between("a",     3, 0, 2), " a ");
  // assertEqual("5",  center_between("a",     4, 0, 3), " a. ");
  // assertEqual("6",  center_between("a",     5, 0, 4), " .a. ");
  //
  // assertEqual("7",  center_between("hello", 9, 0, 8), " .hello. ");
  // assertEqual("8",  center_between("hello", 9, 1, 8), "  hello. ");
  // assertEqual("9",  center_between("hello", 9, 2, 8), "   hello ");
  // assertEqual("10", center_between("hello", 9, 3, 8), "   hello ");
  // assertEqual("11", center_between("hello", 9, 4, 8), "    hello");
  // assertEqual("12", center_between("hello", 9, 5, 8), "    hello");
  // assertEqual("13", center_between("hello", 9, 6, 8), "    hello");
  // assertEqual("14", center_between("hello", 9, 7, 8), "    hello");
  // assertEqual("15", center_between("hello", 9, 8, 8), "    hello");
  //
  // assertEqual("16",  center_between("hello", 9, 0, 7), " hello.  ");
  // assertEqual("17",  center_between("hello", 9, 0, 6), " hello   ");
  // assertEqual("18",  center_between("hello", 9, 0, 5), "hello    ");
  // assertEqual("19",  center_between("hello", 9, 0, 4), "hello    ");
  // assertEqual("20",  center_between("hello", 9, 0, 3), "hello    ");
  // assertEqual("21",  center_between("hello", 9, 0, 2), "hello    ");
  // assertEqual("22",  center_between("hello", 9, 0, 1), "hello    ");
  // assertEqual("23",  center_between("hello", 9, 0, 0), "hello    ");
  //
  // assertEqual("24",  center_between("hello", 9, 1, 7), "  hello  ");
  // assertEqual("25",  center_between("hello", 9, 1, 6), " hello   ");
  // assertEqual("26",  center_between("hello", 9, 2, 6), "  hello  ");
  // assertEqual("27",  center_between("hello", 9, 2, 5), " hello   ");
  // assertEqual("28",  center_between("hello", 9, 3, 5), "  hello  ");
  // assertEqual("29",  center_between("hello", 9, 3, 4), " hello   ");
  // assertEqual("30",  center_between("hello", 9, 4, 4), "  hello  ");
  //
//  hello
// 012345678
//    lr


  return 0;
}

string center_between(string s, int width, int left, int right) {
  assert(s.length() <= width);
  assert(0 <= left);
  assert(left <= right);
  assert(right <= width);

  int start_pos = 0;
  int best_val = INT_MAX;

  for(int cur_start_pos = 0; cur_start_pos <= width - s.length(); cur_start_pos++) {
    int left_chars = left - cur_start_pos;
    int right_chars = cur_start_pos + s.length() - 1 - right;
    int val = abs(right_chars - left_chars);
    // cout << "cur: " << cur_start_pos
    //      << "; left_chars: " << left_chars
    //      << "; right_chars: " << right_chars
    //      << "; val: " << val
    //      << endl;

    if(val < best_val) {
      // cout << "new best." << endl;
      start_pos = cur_start_pos;
      best_val = val;
    }
  }

  string output(width, ' ');

  for(int i = 0; i < width; i++) {
    if(i < start_pos) {
      // cout << "branch 1" << endl;
      output[i] = (i > left ? '.' : ' ');
    } else if(start_pos <= i && i < start_pos + s.length()) {
      // cout << "branch 2" << endl;
      output[i] = s[i - start_pos];
    } else {
      // cout << "branch 3" << endl;
      output[i] = (i < right ? '.' : ' ');
    }
  }

  return output;
}

#endif
