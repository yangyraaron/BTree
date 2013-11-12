#include <stdlib.h>
#include <assert.h>

#include "avltree.h"

static void subtree_free(avltree_node_p);
static avltree_node_p create_node(avltree_node_p, int);
static void subtree_add(avltree_node_p, int);
static void verify_balance(avltree_node_p);
static avltree_node_p get_left_leaf(avltree_node_p);
static int get_depth(avltree_node_p);
//static int get_depth_from_bottom(avltree_node_p, avltree_node_p);
static void rotate_ll(avltree_node_p);
static void rotate_rr(avltree_node_p);
static void rotate_lr(avltree_node_p);
static void rotate_rl(avltree_node_p);

avltree_p avltree_create() {
    avltree_p tree = (avltree_p) malloc(sizeof (avltree));
    assert(tree != NULL);

    tree->root = NULL;

    return tree;
}

void avltree_free(avltree_p tree) {
    if (NULL == tree || NULL == tree->root) return;

    subtree_free(tree->root);

    free(tree);
}

void subtree_free(avltree_node_p node) {
    if (NULL == node) return;

    if (NULL != node->left) subtree_free(node->left);
    if (NULL != node->right) subtree_free(node->right);

    free(node);
}

static avltree_node_p create_node(avltree_node_p parent, int value) {
    avltree_node_p node = (avltree_node_p) malloc(sizeof (avltree_node));
    assert(NULL != node);
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    node->parent = parent;

    return node;
}

static void subtree_add(avltree_node_p node, int value) {
    if (value == node->value) return;

    if (value < node->value) {
        if (NULL == node->left)
            node->left = create_node(node, value);
        else
            subtree_add(node->left, value);
    } else {
        if (NULL == node->right)
            node->right = create_node(node, value);
        else
            subtree_add(node->right, value);
    }
}

static avltree_node_p get_left_leaf(avltree_node_p node) {
    avltree_node_p lnode = NULL;
    while (NULL != node->left) {
        lnode = node->left;
    }

    return lnode;
}

static int get_depth(avltree_node_p node) {
    int depth = 0, ldepth = 0, rdepth = 0;

    if (NULL == node) return depth;

    avltree_node_p lnode = get_left_leaf(node);
    if (NULL != lnode) ldepth++;
    avltree_node_p parent = lnode->parent;

    while (parent != node) {
        rdepth = get_depth(node->right);
        depth = ldepth > rdepth ? ldepth : rdepth;
         
        parent = parent->parent;
    }

    return depth++;

}

static int get_depth_from_bottom(avltree_node_p node) {
    int depth = 1, ldepth = 0, rdepth = 0;
    avltree_node_p parent = node->parent;

    //if the node is right child
    if (node->value > parent->value) {
        rdepth = 1;
        ldepth = get_depth(parent->left);
    } else {
        ldepth = 1;
        rdepth = get_depth(parent->right);
    }

    int balance = ldepth - rdepth;
    if (balance == -2 || balance == 2) {

    }
    
    return depth;
}


void avltree_add(avltree_p tree, int value) {

}