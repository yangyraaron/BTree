
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "btree.h"
#include "linklist.h"

static int caculate_subtree_depth(BTREE_NODE);
static void free_node(BTREE_NODE);
static int is_subtree_balance(BTREE_NODE);

BTREE btree_create() {
    BTREE tree = (BTREE) malloc(sizeof (btree));
    tree->root = NULL;
    assert(tree != NULL);

    return tree;
}

int btree_get_depth(BTREE tree) {
    if (tree->root == NULL) return 0;

    return caculate_subtree_depth(tree->root);
}

static int caculate_subtree_depth(BTREE_NODE node) {
    //printf("arrivate at node %d\n",node->data);

    if (node->left == NULL && node->right == NULL) return 1;

    int ldepth = 0, rdepth = 0;

    if (node->left != NULL)
        ldepth = caculate_subtree_depth(node->left) + 1;

    if (node->right != NULL)
        rdepth = caculate_subtree_depth(node->right) + 1;

    return ldepth > rdepth ? ldepth : rdepth;
}

void btree_free(BTREE tree) {
    if (tree->root != NULL)
        free_node(tree->root);

    tree->root = NULL;
    free(tree);
}

static void free_node(BTREE_NODE node) {
    if (node == NULL) return;

    if (node->left != NULL) free_node(node->left);
    if (node->right != NULL) free_node(node->right);

    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    free(node);

    node = NULL;
}

int btree_is_balance(BTREE tree) {
    if (tree->root == NULL) return 0;

    return is_subtree_balance(tree->root);
}

static int is_subtree_balance(BTREE_NODE node) {
    if (node->left == NULL && node->right == NULL) {
        //printf("node %d is a leaf node\n",node->data);
        return 1;
    }

    int lbalance = 1, rbalance = 1;
    int ldepth = 0, rdepth = 0;

    if (node->left != NULL) {
        lbalance = is_subtree_balance(node->left);
    }
    if (node->right != NULL) {
        rbalance = is_subtree_balance(node->right);
    }

    /*if the left subtree or right subtree is not balance then the tree is not balance*/
    if (!(lbalance & rbalance)) return 0;

    if (node->left != NULL)
        ldepth = caculate_subtree_depth(node->left);
    if (node->right != NULL)
        rdepth = caculate_subtree_depth(node->right);

    int sub = ldepth - rdepth;
    //printf("node %d left: %d right: %d\n",node->data,ldepth,rdepth);

    int value = (sub >= -1)&(sub <= 1);
    //printf("the balance of node %d : %s\n",node->data,(value?"yes":"no"));

    return value;
}

BTREE_NODE btree_get_first_leaf(BTREE_NODE node) {
    if (node == NULL) return NULL;

    BTREE_NODE leaf = node;
    while (leaf != NULL) {
        if (leaf->left != NULL)
            leaf = leaf->left;
        else if (leaf->right != NULL)
            leaf = leaf->right;
        else
            break;
    }

    return leaf;
}

static int caculate_node_balance(BTREE_NODE node) {
    BTREE_NODE leaf = btree_get_first_leaf(node);

    if (leaf == NULL) return 1;

    int depth = 0, is_balance = 1;

    BTREE_NODE parent = leaf, prev_parent = leaf;

    while (parent != node->parent) {
        int r_depth = 0;

        if (parent->left == prev_parent) {
            if (parent->right != NULL) {
                r_depth = caculate_node_balance(parent->right);
            }

            int value = r_depth - depth;

            if (value > 1 || value<-1) {
                is_balance = 0;
            }
            depth = depth > r_depth ? depth : r_depth;
        }

        depth++;
        prev_parent = parent;
        parent = parent->parent;

        if (is_balance == 0) return is_balance;
    }

    return is_balance == 0 ? 0 : depth;
}

int btree_is_balance_v1(BTREE tree) {
    if (tree == NULL || tree->root == NULL) return 0;

    return caculate_node_balance(tree->root);
}

void btree_add_left(BTREE_NODE node, BTREE_NODE left) {
    if (node == NULL || left == NULL) return;

    node->left = left;
    left->parent = node;
}

void btree_add_right(BTREE_NODE node, BTREE_NODE right) {
    if (node == NULL || right == NULL) return;

    node->right = right;
    right->parent = node;
}

static LINK_LIST get_path(BTREE_NODE node) {
    LINK_LIST path = lk_list_create();
    BTREE_NODE parent = node->parent;
    while (parent != NULL) {
        lk_list_append(path,parent);
        parent = parent->parent;
    }

    return path;
}

static BTREE_NODE get_first_same(LINK_LIST list1,LINK_LIST list2){
    while(list1->size>0){
        BTREE_NODE node1 = lk_list_pop(list1);
        BTREE_NODE node2 = lk_list_pop(list2);
        
        if(node1->data = node2->data)
            return node1;
    }
    
    return NULL;
}

BTREE_NODE btree_get_first_same_parent(BTREE_NODE node1, BTREE_NODE node2) {
    if (node1 == NULL || node2 == NULL) return NULL;
    
    //if one of node is the root then has not same parent
    //if(node1->parent==NULL || node2->parent == NULL) return NULL;
    
    if(node1->parent==node2) return node2;
    
    if(node2->parent == node1) return node1;
    
    LINK_LIST path1 = get_path(node1);
    LINK_LIST path2 = get_path(node2);
    
    int sub = path1->size-path2->size;
    //the level node2 at is deeper
    if(sub<0){
        //sub = abs(sub);
        while(sub<0){
            lk_list_pop(path2);
            sub++;
        }
    }else if(sub>0){
        while(sub>0){
            lk_list_pop(path1);
            sub--;
        }
    }
    BTREE_NODE parent = get_first_same(path1,path2);
    lk_list_free(path1);
    lk_list_free(path2);
    
    return parent;
}

BTREE_NODE btree_get_first_same_parent_order(BTREE tree,BTREE_NODE node1,BTREE_NODE node2){
    BTREE_NODE node = tree->root,left=NULL,right=NULL;
//    if(node1->left==node2 || node1->right==node2) return node1;
//    if(node2->left == node1 || node2->right==node1) return node2;
    if((node1->data-node2->data)<0){
        left = node1;
        right = node2;
    }else{
        left = node2;
        right = node1;
    }
    
    while(NULL!=node){
        if((node->data>left->data) && (node->data<right->data)){
            return node;
        }else if(node==left){
            return left;
        }else if(node==right){
            return right;
        }else if(node->data>right->data){
            node = node->left;
        }else{
            node = node->right;
        }
    }
    
    return node;
}

