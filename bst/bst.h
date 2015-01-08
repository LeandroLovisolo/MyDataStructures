#ifndef __BST_H__
#define __BST_H__

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <climits>
#include <cassert>

template<typename node_t>
class bst_node_t {
public:
  bst_node_t(int value, node_t *parent = nullptr) {
    this->value = value;
    this->parent = parent;
    this->left = this->right = nullptr;
  }

  ~bst_node_t() {
    if(this->left != nullptr) delete this->left;
    if(this->right != nullptr) delete this->right;
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
  bst_node(int value, bst_node *parent = nullptr) : bst_node_t(value, parent) {}
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
  void transplant(node_t *n, node_t *m);
  node_t *root;

private:
  bool is_bst_r(node_t *node);
  std::tuple<std::vector<std::string>, int> print_node(node_t *node);
  std::tuple<std::string, int> center_between(
      const std::string &s, int width, int left, int right,
      char left_internal_padding, char right_internal_padding);
  std::string padding_right(const std::string &s, int w);
  std::string padder(int w);
};

template<typename node_t>
bst<node_t>::bst() {
  this->root = nullptr;
}

template<typename node_t>
bst<node_t>::~bst() {
  if(this->root != nullptr) delete this->root;
}

template<typename node_t>
node_t* bst<node_t>::find(int value) {
  node_t *current = root;
  while(current != nullptr) {
    if(current->value == value) return current;
    if(value < current->value) current = current->left;
    else current = current->right;
  }
  return nullptr;
}

template<typename node_t>
node_t* bst<node_t>::insert(int value) {
  if(root == nullptr) {
    return root = new node_t(value);
  } else {
    node_t *parent = root;
    while(true) {
      if(value == parent->value) return nullptr;

      node_t *next;
      if(value < parent->value) next = parent->left;
      else next = parent->right;

      if(next == nullptr) break;
      parent = next;
    };
    if(value < parent->value) return parent->left = new node_t(value, parent);
    else return parent->right = new node_t(value, parent);
  }
}

template<typename node_t>
bool bst<node_t>::remove(int value) {
  node_t *node = find(value);
  if(node == nullptr) return false;

  if(node->left == nullptr) {
    transplant(node, node->right);
  } else if(node->right == nullptr) {
    transplant(node, node->left);
  } else {
    node_t *successor = node->right;
    while(successor->left != nullptr) successor = successor->left;
    if(successor->parent != node) {
      transplant(successor, successor->right);
      successor->right = node->right;
      successor->right->parent = successor;
    }
    transplant(node, successor);
    successor->left = node->left;
    successor->left->parent = successor;
  }

  node->left = nullptr;
  node->right = nullptr;
  delete node;

  return true;
}

template<typename node_t>
void bst<node_t>::transplant(node_t *n, node_t *m) {
  if(n->parent == nullptr) {
    root = m;
  } else if(n->parent->left == n) {
    n->parent->left = m;
  } else {
    n->parent->right = m;
  }
  if(m != nullptr) {
    m->parent = n->parent;
  }
}

template<typename node_t>
bool bst<node_t>::is_bst() {
  return is_bst_r(root);
}

template<typename node_t>
bool bst<node_t>::is_bst_r(node_t *node) {
  if(node == nullptr) return true;
  bool left_ok = node->left == nullptr ||
                 (node->left->value < node->value && is_bst_r(node->left));
  if(!left_ok) return false;
  bool right_ok = node->right == nullptr ||
                  (node->right->value > node->value && is_bst_r(node->right));
  return right_ok;
}

template<typename node_t>
std::tuple<std::string, int>
bst<node_t>::center_between(
    const std::string &s, int width, int left, int right,
    char left_internal_padding, char right_internal_padding) {
  assert(s.length() <= width);
  assert(0 <= left);
  assert(left <= right);
  assert(right <= width);

  int start_pos = 0;
  int best_val = INT_MAX;

  for(int cur_start_pos = 0;
      cur_start_pos <= width - s.length();
      cur_start_pos++) {
    int left_chars = left - cur_start_pos;
    int right_chars = cur_start_pos + s.length() - 1 - right;
    int val = abs(right_chars - left_chars);
    if(val < best_val) {
      start_pos = cur_start_pos;
      best_val = val;
    }
  }

  std::string output(width, ' ');

  for(int i = 0; i < width; i++) {
    if(i < start_pos) {
      output[i] = (i > left ? left_internal_padding : ' ');
    } else if(start_pos <= i && i < start_pos + s.length()) {
      output[i] = s[i - start_pos];
    } else {
      output[i] = (i < right ? right_internal_padding : ' ');
    }
  }

  return make_tuple(output, start_pos);
}

template<typename node_t>
std::string bst<node_t>::padding_right(const std::string &s, int w) {
  int padding = w - s.length();
  std::string spaces(padding, ' ');
  return s + spaces;
}

template<typename node_t>
std::string bst<node_t>::padder(int w) {
  return std::string(std::max(0, w), ' ');
}

template<typename node_t>
std::tuple<std::vector<std::string>, int>
bst<node_t>::print_node(node_t *node) {
  std::vector<std::string> output;
  int root_label_midpoint = 0;

  if(node == nullptr) {
    // Do nothing
  } else if(node->left == nullptr && node->right == nullptr) {
    output = { node->label() };
    root_label_midpoint = node->label().length() / 2;
  } else {
    std::string label = node->label();

    // Print left subtree
    std::vector<std::string> left_lines;
    int left_label_midpoint;
    std::tie(left_lines, left_label_midpoint) = print_node(node->left);

    // Print right right
    std::vector<std::string> right_lines;
    int right_label_midpoint;
    std::tie(right_lines, right_label_midpoint) = print_node(node->right);

    // Compute width
    int left_width = left_lines.empty() ? 0 : left_lines[0].length();
    int right_width = right_lines.empty() ? 0 : right_lines[0].length();
    int width = std::max((int) label.length(), left_width + right_width + 1);

    // Compute label line
    std::string label_line;
    int label_start_pos;
    std::tie(label_line, label_start_pos) = center_between(
        label, width,
        left_label_midpoint,
        left_width + 1 + right_label_midpoint,
        node->left  == nullptr ? ' ' : '_',
        node->right == nullptr ? ' ' : '_');

    // Compute label midpoint
    root_label_midpoint = label_start_pos + label.length() / 2;

    // Print label
    output.push_back(label_line);

    // Print edges
    std::string edges_line;
    if(left_width == 0) {
      edges_line = padding_right(padder(right_label_midpoint + 1) + "\\",
                                 width);
    } else if(right_width == 0) {
      edges_line = padding_right(padder(left_label_midpoint) + "/", width);
    } else {
      std::string left = padding_right(padder(left_label_midpoint) + "/",
                                       left_width);
      std::string right = padder(right_label_midpoint) + "\\";
      edges_line = padding_right(left + " " + right, width);
    }
    output.push_back(edges_line);

    // Append subtrees
    for(int i = 0; i < std::max(left_lines.size(), right_lines.size()); i++) {
      std::string left = (i >= left_lines.size() ?
          padder(left_width) : left_lines[i]);

      std::string right = (i >= right_lines.size() ?
          padder(right_width) : right_lines[i]);

      output.push_back(left + " " + right);
    }
  }

  return make_tuple(output, root_label_midpoint);
}

template<typename node_t>
std::string bst<node_t>::print() {
  std::string output;
  if(root == nullptr) {
    output = "Empty tree.";
  } else {
    auto lines = std::get<0>(print_node(root));
    for(auto line : lines) {
      output += line + "\n";
    }
  }
  return output;
}

#endif
