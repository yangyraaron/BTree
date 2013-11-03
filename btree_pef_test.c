#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "btree.h"
#include "linklist.h"

static void build_level_nodes(LINK_LIST,int);
static int build_left_right(BTREE_NODE,int);
static BTREE build_large_tree(int);

static BTREE_NODE create_node(const int data){
    BTREE_NODE node = (BTREE_NODE)malloc(sizeof(btree_node));
    node->data = data;
    
    return node;
}

void btree_pef_balance_test(int number){
    BTREE tree = build_large_tree(number);
    
    clock_t start,end;
    double elapsed;
    
    start = clock();
    
    int balance=btree_is_balance(tree);
    
    end = clock();
    
    elapsed = (double)(end-start)/CLOCKS_PER_SEC;
    
    //printf("CLOCKS_PER_SEC is %f\n",(double)CLOCKS_PER_SEC);
    
    printf("the elapse is %f\n",elapsed);
    assert(balance);
    
    btree_free(tree);

}

void btree_pef_balance_v1_test(int number){
    BTREE tree = build_large_tree(number);
    
    clock_t start,end;
    double elapsed;
    
    start = clock();
    
    int balance=btree_is_balance_v1(tree);
    
    end = clock();
    
    elapsed = (double)(end-start)/CLOCKS_PER_SEC;
    
    //printf("CLOCKS_PER_SEC is %f\n",(double)CLOCKS_PER_SEC);
    
    printf("the elapse is %f\n",elapsed);
    assert(balance);
    
    btree_free(tree);
}

 BTREE build_large_tree(int count){
   BTREE tree = btree_create();
   LINK_LIST list = lk_list_create();
   
   tree->root = create_node(count);
   lk_list_append(list,tree->root);
   
   build_level_nodes(list,count-1);
    
   lk_list_free(list);
   
   return tree;
}

static void build_level_nodes(LINK_LIST list,int count){
    while((list->size>0) && count>0){
        BTREE_NODE node = lk_list_pop(list);
        count = build_left_right(node,count);
        
        lk_list_append(list,node->left);
        lk_list_append(list,node->right);
    }
}

static int build_left_right(BTREE_NODE node,int count){
    if(count>0){
        BTREE_NODE left = create_node(count);
        //node->left = left;
        btree_add_left(node,left);
        count--;
    }
    
    if(count>0){
        BTREE_NODE right = create_node(count);
        //node->right = right;
        btree_add_right(node,right);
        count--;
    } 
    
    return count;
}
