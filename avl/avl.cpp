#include "avl.h"

using namespace std;
    
avl_node::avl_node(int value, avl_node *parent) : bst_node_t(value, parent) {
    height = 0;
}

string avl_node::label() {
    return to_string(value) + " (" + to_string(height) + ")";
}

void avl_node::update_height() {
    if(left == 0 && right == 0) {
        height = 0;
    } else {
        height = max(left ? left->height : 0, right ? right->height : 0) + 1;
    }
}

avl::avl() {
}

avl::~avl() {
}

avl_node* avl::insert(int value) {
    avl_node *new_node = bst<avl_node>::insert(value);
    rebalance(new_node);
    return new_node;
}

void avl::rotate_left(avl_node *node) {
    avl_node *a = node->left,
             *b = node->right->left,
             *c = node->right->right;
    node->left = node->right;
    node->left->parent = node;
    swap(node->value, node->left->value);
    node->left->left = a;
    if(a != nullptr) a->parent = node->left;
    node->left->right = b;
    if(b != 0) b->parent = node->left;
    node->right = c;
    if(c != 0) c->parent = node;
    node->left->update_height();
}

void avl::rotate_right(avl_node *node) {
    avl_node *a = node->left->left,
             *b = node->left->right,
             *c = node->right;
    node->right = node->left;
    node->right->parent = node;
    swap(node->value, node->left->value);
    node->left = a;
    if(a != nullptr) a->parent = node;
    node->right->left = b;
    if(b != 0) b->parent = node->right;
    node->right->right = c;
    if(c != 0) c->parent = node->right;
    node->right->update_height();
}

int height(avl_node *node) {
    return node == 0 ? 0 : node->height;
}

void avl::rebalance(avl_node *node) {
    if(node == 0) return;
    if(height(node->left) > height(node->right) + 1) {
        if(height(node->left->right) > height(node->left->left)) {
            rotate_left(node->left);
        }
        rotate_right(node);
    } else if(height(node->right) > height(node->left) + 1) {
        if(height(node->right->left) > height(node->right->right)) {
            rotate_right(node->right);
        }
        rotate_left(node);
    }
    node->update_height();
    rebalance(node->parent);
}

bool avl::is_avl() {
    return is_avl_r(root);
}

bool avl::is_avl_r(avl_node *node) {
    if(node == 0) return true;
    return is_avl_r(node->left) &&
           is_avl_r(node->right) &&
           abs(height(node->left) - height(node->right)) <= 1;
}