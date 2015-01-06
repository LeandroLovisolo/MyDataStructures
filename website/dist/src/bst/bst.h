#ifndef __BST_H__
#define __BST_H__

#include <iostream>
#include <tuple>
#include <vector>
#include <string>

template<typename node_t>
class bst_node_t {
public:
  bst_node_t(int value, node_t *parent = 0) {
    this->value = value;
    this->parent = parent;
    this->left = this->right = 0;
  }

  ~bst_node_t() {
    if(this->left != 0) delete this->left;
    if(this->right != 0) delete this->right;
  }

  std::string label() {
    return std::to_string(value);
  }

  int value;
  node_t *parent;
  node_t *left;
  node_t *right;
};

class bst_node : public bst_node_t<bst_node> {
public:
  bst_node(int value, bst_node *parent = 0) : bst_node_t(value, parent) {}
};

template<typename node_t = bst_node>
class bst {
public:
  bst();
  ~bst();

  node_t* find(int value);
  node_t* insert(int value);
  bool remove(int value);

  bool is_bst();
  std::string print();

protected:
  node_t *root;

private:
  void transplant(node_t *n, node_t *m);
  bool is_bst_r(node_t *node);
  std::tuple<std::vector<std::string>, int, int> print_r(node_t *node);
  std::string center(const std::string &s, int w);

};

template<typename node_t>
bst<node_t>::bst() {
  this->root = 0;
}

template<typename node_t>
bst<node_t>::~bst() {
  if(this->root != 0) delete this->root;
}

template<typename node_t>
node_t* bst<node_t>::find(int value) {
  node_t *current = root;
  while(current != 0) {
    if(current->value == value) return current;
    if(value < current->value) current = current->left;
    else current = current->right;
  }
  return 0;
}

template<typename node_t>
node_t* bst<node_t>::insert(int value) {
  if(root == 0) {
    return root = new node_t(value);
  } else {
    node_t *parent = root;
    while(true) {
      if(value == parent->value) return 0;

      node_t *next;
      if(value < parent->value) next = parent->left;
      else next = parent->right;

      if(next == 0) break;
      parent = next;
    };
    if(value < parent->value) return parent->left = new node_t(value, parent);
    else return parent->right = new node_t(value, parent);
  }
}

template<typename node_t>
bool bst<node_t>::remove(int value) {
  node_t *node = find(value);
  if(node == 0) return false;

  if(node->left == 0) {
    transplant(node, node->right);
  } else if(node->right == 0) {
    transplant(node, node->left);
  } else {
    node_t *successor = node->right;
    while(successor->left != 0) successor = successor->left;
    if(successor->parent != node) {
      transplant(successor, successor->right);
      successor->right = node->right;
      successor->right->parent = successor;
    }
    transplant(node, successor);
    successor->left = node->left;
    successor->left->parent = successor;
  }

  return true;
}


template<typename node_t>
void bst<node_t>::transplant(node_t *n, node_t *m) {
  if(n->parent == 0) {
    root = m;
  } else if(n->parent->left == n) {
    n->parent->left = m;
  } else {
    n->parent->right = m;
  }
  if(m != 0) {
    m->parent = n->parent;
  }
}

template<typename node_t>
bool bst<node_t>::is_bst() {
  return is_bst_r(root);
}

template<typename node_t>
bool bst<node_t>::is_bst_r(node_t *node) {
  if(node == 0) return true;
  bool left_ok = node->left == 0 ||
                 (node->left->value < node->value && is_bst_r(node->left));
  if(!left_ok) return false;
  bool right_ok = node->right == 0 ||
                  (node->right->value > node->value && is_bst_r(node->right));
  return right_ok;
}

template<typename node_t>
std::string bst<node_t>::print() {
  std::string output;
  if(root == 0) {
    output = "Empty tree.\n";
  } else {
    auto tuple = print_r(root);
    for(auto line : std::get<0>(tuple)) {
      output += line + "\n";
    }
  }
  return output;
}

template<typename node_t>
std::tuple<std::vector<std::string>, int, int> bst<node_t>::print_r(node_t *node) {
  if(node == 0) return make_tuple(std::vector<std::string>(), 0, 0);

  std::string label = node->label();

  auto left_tuple = print_r(node->left);
  std::vector<std::string> left_lines = std::get<0>(left_tuple);
  int left_pos = std::get<1>(left_tuple);
  int left_width = std::get<2>(left_tuple);

  auto right_tuple = print_r(node->right);
  std::vector<std::string> right_lines = std::get<0>(right_tuple);
  int right_pos = std::get<1>(right_tuple);
  int right_width = std::get<2>(right_tuple);

  int middle = std::max(right_pos + left_width - left_pos + 1, (int) label.length());
  middle = std::max(middle, 2);
  int pos = left_pos + middle / 2;
  int width = left_pos + middle + right_width - right_pos;

  while(left_lines.size() < right_lines.size()) {
    left_lines.push_back(std::string(left_width, ' '));
  }

  while(right_lines.size() < left_lines.size()) {
    right_lines.push_back(std::string(right_width, ' '));
  }

  if((middle - label.length()) % 2 == 1 &&
     node->parent != 0 &&
     node == node->parent->left &&
     label.length() < middle) {
    label += ".";
  }

  label = center(label, middle);
  if(label[0] == '.') {
    label = " " + label.substr(1);
  }
  if(label[label.length() - 1] == '.') {
    label = label.substr(0, label.length() - 1) + " ";
  }

  std::vector<std::string> lines;
  lines.push_back(std::string(left_pos, ' ') +
                  label +
                  std::string(right_width - right_pos, ' '));
  lines.push_back(std::string(left_pos, ' ') + "/" +
                  std::string(middle - 2, ' ') + "\\" +
                  std::string(right_width - right_pos, ' '));
  for(int i = 0; i < std::min(left_lines.size(), right_lines.size()); i++) {
    lines.push_back(left_lines[i] +
                    std::string(width - left_width - right_width, ' ') +
                    right_lines[i]);
  }

  return std::make_tuple(lines, pos, width);
}

template<typename node_t>
std::string bst<node_t>::center(const std::string &s, int w) {
  int padding = w - s.length();
  std::string spaces(padding / 2, '.');
  std::string padded = spaces + s + spaces;
  if(padding > 0 && padding % 2 == 1) {
    padded += ".";
  }
  return padded;
}

#endif
