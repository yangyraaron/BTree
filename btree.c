
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"

static int caculate_subtree_depth(BTREE_NODE);
static void free_node(BTREE_NODE);
static int is_subtree_balance(BTREE_NODE);

BTREE btree_create(){
    BTREE tree = (BTREE) malloc(sizeof(btree));
    assert(tree!=NULL);
    
    return tree;
}

int btree_get_depth(BTREE tree){
    if(tree->root==NULL) return 0;
    
    return caculate_subtree_depth(tree->root);
}

static int caculate_subtree_depth(BTREE_NODE node){
    //printf("arrivate at node %d\n",node->data);
    
    if(node->left==NULL && node->right==NULL) return 1;
    
    int ldepth=0,rdepth=0;
    
    if(node->left!=NULL)
        ldepth=caculate_subtree_depth(node->left)+1;
    
    if(node->right!=NULL)
        rdepth=caculate_subtree_depth(node->right)+1;
    
    return ldepth>rdepth?ldepth:rdepth;
}

void btree_free(BTREE tree){
    if(tree->root!=NULL)
        free_node(tree->root);
    
    free(tree);
}

static void free_node(BTREE_NODE node){
    if(node==NULL) return;
    
    if(node->left!=NULL) free_node(node->left);
    if(node->right!=NULL) free_node(node->right);
    
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    
    free(node);
    
    node = NULL;
}

int btree_is_balance(BTREE tree){
    if(tree->root == NULL) return 0;
    
    return is_subtree_balance(tree->root);
}

static int is_subtree_balance(BTREE_NODE node){
    if(node->left==NULL && node->right==NULL){
        //printf("node %d is a leaf node\n",node->data);
        return 1;
    }
    
    int lbalance=1,rbalance=1;
    int ldepth=0,rdepth=0;
    
    if(node->left!=NULL){
        lbalance = is_subtree_balance(node->left);
    }
    if(node->right!=NULL){
        rbalance = is_subtree_balance(node->right);
    }
    
    /*if the left subtree or right subtree is not balance then the tree is not balance*/
    if(!(lbalance&rbalance)) return 0;
    
    if(node->left!=NULL)
        ldepth = caculate_subtree_depth(node->left);
    if(node->right!=NULL)
        rdepth = caculate_subtree_depth(node->right);
    
    int sub = ldepth-rdepth;
    //printf("node %d left: %d right: %d\n",node->data,ldepth,rdepth);
    
    int value = (sub>=-1)&(sub<=1);
    //printf("the balance of node %d : %s\n",node->data,(value?"yes":"no"));
    
    return value;
}


BTREE_NODE btree_get_first_leaf(BTREE_NODE node){
    if(node==NULL) return NULL;
    
    BTREE_NODE leaf = node;
    while(leaf!=NULL){
        if(leaf->left!=NULL)
            leaf = leaf->left;
        else if(leaf->right!=NULL)
            leaf = leaf->right;
        else
            break;
    }
    
    return leaf;
}

static int caculate_node_balance(BTREE_NODE node){
    BTREE_NODE leaf = btree_get_first_leaf(node);
    
    if(leaf == NULL) return 1;
    
    int depth=0,is_balance=1;
    
    BTREE_NODE parent = leaf, prev_parent=leaf;
    
    while(parent!=node->parent){
        int r_depth=0;
        
        if(parent->left == prev_parent){
            if(parent->right!=NULL){
                r_depth=caculate_node_balance(parent->right);
            }
            
            int value = r_depth-depth;
            
            if(value>1||value<-1){
                is_balance=0;
            }
            depth = depth>r_depth?depth:r_depth;
        }
        
        depth++;
        prev_parent = parent;
        parent = parent->parent;
        
        if(is_balance==0) return is_balance;
    }
    
    return is_balance==0?0:depth;
}

int btree_is_balance_v1(BTREE tree){
    if(tree==NULL || tree->root==NULL) return 0;
    
    return caculate_node_balance(tree->root);
}

void btree_add_left(BTREE_NODE node,BTREE_NODE left){
    if(node==NULL || left==NULL) return;
    
    node->left = left;
    left->parent = node;
}
void btree_add_right(BTREE_NODE node,BTREE_NODE right){
    if(node==NULL || right == NULL) return;
    
    node->right = right;
    right->parent = node;
}

