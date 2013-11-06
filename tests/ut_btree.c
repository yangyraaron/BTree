/*
 * File:   newcunittest.c
 * Author: wisedulab2
 *
 * Created on Oct 30, 2013, 9:04:55 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "btree.h"

/*
 * CUnit Test Suite
 */


int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

static BTREE_NODE create_node(const int data){
    BTREE_NODE node = (BTREE_NODE)malloc(sizeof(btree_node));
    node->left=NULL;
    node->right=NULL;
    node->parent=NULL;
    node->data = data;
    
    return node;
}

void btree_depth_test(){
    BTREE tree = btree_create();
    CU_ASSERT(tree!=NULL);
    
    /*root is null*/
    int depth = btree_get_depth(tree);
    CU_ASSERT(depth==0);
    
    
    /*root is 1*/
    BTREE_NODE node1 = create_node(1);
    tree->root = node1;
    depth=btree_get_depth(tree);
    CU_ASSERT(depth==1);

    
    /*      1
     *     /
     *    2 
     */
    
    BTREE_NODE node2 = create_node(2);
    node1->left = node2;
    depth = btree_get_depth(tree);
    CU_ASSERT(depth==2);
    
    
    /*      1
     *     / \
          2   3
     */
    BTREE_NODE node3 = create_node(3);
    node1->right = node3;
    depth = btree_get_depth(tree);
    CU_ASSERT(depth==2);
    
    
    /*        1
             / \
     *      2   3
     *     /
     *    4
     */
    BTREE_NODE node4 = create_node(4);
    node2->left = node4;
    depth=btree_get_depth(tree);
    CU_ASSERT(depth==3);
    
    /*        1
             / \
     *      2   3
     *     / \
     *    4   5
     */
    BTREE_NODE node5 = create_node(5);
    node2->right = node5;
    depth=btree_get_depth(tree);
    CU_ASSERT(depth==3);
    
    
    /*        1
             / \
     *      2   3
     *     / \   \
     *    4   5   6
     */
    BTREE_NODE node6 = create_node(6);
    node3->right = node6;
    depth=btree_get_depth(tree);
    CU_ASSERT(depth==3);
    
    
    /*        1
             / \
     *      2   3
     *     / \   \
     *    4   5   6
     *       /
     *      7
     */
    BTREE_NODE node7 = create_node(7);
    node5->right = node7;
    depth=btree_get_depth(tree);
    CU_ASSERT(depth==4);
    
    
    /*        1
             / \
     *      2   3
     *     / \   \
     *    4   5   6
     *       /
     *      7
     *     /
     *    8    
     */
    BTREE_NODE node8 = create_node(8);
    node7->left = node8;
    depth=btree_get_depth(tree);
    CU_ASSERT(depth==5);
    
    btree_free(tree);
    tree->root==NULL;
//    depth=btree_get_depth(tree);
//    CU_ASSERT(depth==0);
}

void testBtree_get_depth() {
    btree_depth_test();
}

void btree_balance_test(){
    BTREE tree = btree_create();
    CU_ASSERT(tree!=NULL);
    
    /*root is null*/
    int balance = btree_is_balance(tree);
    CU_ASSERT(!balance);
    
    /*root is 1*/
    BTREE_NODE node1 = create_node(1);
    tree->root = node1;
    balance=btree_is_balance(tree);
    CU_ASSERT(balance);
    
    /*      1
     *     /
     *    2 
     */
    
    BTREE_NODE node2 = create_node(2);
    node1->left = node2;
    balance = btree_is_balance(tree);
    CU_ASSERT(balance);
    
    /*      1
     *     / 
          2
     *   /
     *  3
     */
    BTREE_NODE node3 = create_node(3);
    node2->left = node3;
    balance = btree_is_balance(tree);
    CU_ASSERT(!balance);
    
    /*      1
     *     / \
          2   3
     */
    node2->left=NULL;
    node1->right = node3;
    balance = btree_is_balance(tree);
    CU_ASSERT(balance);
   
    /*        1
             / \
     *      2   3
     *     /
     *    4
     */
    BTREE_NODE node4 = create_node(4);
    node2->left = node4;
    balance=btree_is_balance(tree);
    CU_ASSERT(balance);
     
    /*        1
             / \
     *      2   3
     *     /
     *    4 
     *     \
     *      5 
     */
    BTREE_NODE node5 = create_node(5);
    node4->right = node5;
    balance=btree_is_balance(tree);
    CU_ASSERT(!balance);
     
    /*        1
             / \
     *      2   3
     *     / \
     *    4   5
     */
    //BTREE_NODE node5 = create_node(5);
    node4->right=NULL;
    node2->right = node5;
    balance=btree_is_balance(tree);
    CU_ASSERT(balance);
    
    /*        1
             / \
     *      2   3
     *     / \   \
     *    4   5   6
     */
    BTREE_NODE node6 = create_node(6);
    node3->right = node6;
    balance=btree_is_balance(tree);
    CU_ASSERT(balance);
    
    /*        1
             / \
     *      2   3
     *     / \   \
     *    4   5   6
     *       /
     *      7
     */
    BTREE_NODE node7 = create_node(7);
    node5->right = node7;
    balance=btree_is_balance(tree);
    CU_ASSERT(balance);

    /*        1
             / \
     *      2   3
     *     / \   \
     *    4   5   6
     *       /
     *      7
     *     /
     *    8    
     */
    BTREE_NODE node8 = create_node(8);
    node7->left = node8;
    balance=btree_is_balance(tree);
    CU_ASSERT(!balance);
    
    btree_free(tree);
}

void testBtree_is_balance() {
    btree_balance_test();
}

void btree_balance_v1_test(){
    BTREE tree = btree_create();
    CU_ASSERT(tree!=NULL);
    
    /*root is null*/
    int balance = btree_is_balance_v1(tree);
    CU_ASSERT(!balance);
    
    /*root is 1*/
    BTREE_NODE node1 = create_node(1);
    tree->root = node1;
    balance=btree_is_balance_v1(tree);
    CU_ASSERT(balance);
    
    /*      1
     *     /
     *    2 
     */
    
    BTREE_NODE node2 = create_node(2);
    //node1->left = node2;
    btree_add_left(node1,node2);
    balance = btree_is_balance_v1(tree);
    CU_ASSERT(balance);
    
    /*      1
     *     / 
          2
     *   /
     *  3
     */
    BTREE_NODE node3 = create_node(3);
    //node2->left = node3;
    btree_add_left(node2,node3);
    balance = btree_is_balance_v1(tree);
    CU_ASSERT(!balance);
    
    /*      1
     *     / \
          2   3
     */
    node2->left=NULL;
    //node1->right = node3;
    btree_add_right(node1,node3);
    balance = btree_is_balance_v1(tree);
    CU_ASSERT(balance);
   
    /*        1
             / \
     *      2   3
     *     /
     *    4
     */
    BTREE_NODE node4 = create_node(4);
    //node2->left = node4;
    btree_add_left(node2,node4);
    balance=btree_is_balance_v1(tree);
    CU_ASSERT(balance);
     
    /*        1
             / \
     *      2   3
     *     /
     *    4 
     *     \
     *      5 
     */
    BTREE_NODE node5 = create_node(5);
    //node4->right = node5;
    btree_add_right(node4,node5);
    balance=btree_is_balance_v1(tree);
    CU_ASSERT(!balance);
     
    /*        1
             / \
     *      2   3
     *     / \
     *    4   5
     */
    //BTREE_NODE node5 = create_node(5);
    node4->right=NULL;
    //node2->right = node5;
    btree_add_right(node2,node5);
    balance=btree_is_balance_v1(tree);
    CU_ASSERT(balance);
    
    /*        1
             / \
     *      2   3
     *     / \   \
     *    4   5   6
     */
    BTREE_NODE node6 = create_node(6);
    //node3->right = node6;
    btree_add_right(node3,node6);
    balance=btree_is_balance_v1(tree);
    CU_ASSERT(balance);
    
    /*        1
             / \
     *      2   3
     *     / \   \
     *    4   5   6
     *       /
     *      7
     */
    BTREE_NODE node7 = create_node(7);
    //node5->right = node7;
    btree_add_right(node5,node7);
    balance=btree_is_balance_v1(tree);
    CU_ASSERT(balance);

    /*        1
             / \
     *      2   3
     *     / \   \
     *    4   5   6
     *       /
     *      7
     *     /
     *    8    
     */
    BTREE_NODE node8 = create_node(8);
    //node7->left = node8;
    btree_add_left(node7,node8);
    balance=btree_is_balance_v1(tree);
    CU_ASSERT(!balance);
    
    btree_free(tree);
}

void testBtree_is_balance_v1(){
    btree_balance_v1_test();
}

void testBtree_get_first_same_parent(){
    BTREE tree = btree_create();
    
    /*    1
     *   /
     *  2
     */
    BTREE_NODE root = create_node(1);
    tree->root = root;
    BTREE_NODE node2 = create_node(2);
    btree_add_left(root,node2);
    
    BTREE_NODE parent = btree_get_first_same_parent(root,node2);
    CU_ASSERT(parent==root);
    
    /*      1
     *     / \
     *    2   3
     */
    BTREE_NODE node3 = create_node(3);
    btree_add_right(root,node3);
    parent = btree_get_first_same_parent(node2,node3);
    CU_ASSERT(parent == root);
    
    /*      1
     *     / \
     *    2   3
     *   / \
     *  4   5
     *       \
     *        6 
     */
    BTREE_NODE node4 = create_node(4);
    BTREE_NODE node5 = create_node(5);
    BTREE_NODE node6 = create_node(6);
    btree_add_left(node2,node4);
    btree_add_right(node2,node5);
    btree_add_right(node5,node6);
    parent = btree_get_first_same_parent(node4,node6);
    CU_ASSERT(parent == node2);
    parent = btree_get_first_same_parent(node6,node3);
    CU_ASSERT(parent == root);
    
    btree_free(tree);
    
}

void testBtree_get_frist_same_parent_order(){
    BTREE tree = btree_create();
    CU_ASSERT(tree!=NULL);
    
    BTREE_NODE node1 = create_node(20);
    BTREE_NODE node2 = create_node(10);
    BTREE_NODE node3 = create_node(30);
    BTREE_NODE node4 = create_node(5);
    BTREE_NODE node5 = create_node(12);
    BTREE_NODE node6 = create_node(25);
    BTREE_NODE node7 = create_node(35);
    BTREE_NODE node8 = create_node(3);
    BTREE_NODE node9 = create_node(7);
    
    tree->root = node1;
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;
    node4->left = node8;
    node4->right = node9;
    
    BTREE_NODE node = btree_get_first_same_parent_order(tree,node8,node5);
    CU_ASSERT(node == node2);
    
    btree_free(tree);
    
    /**     4
     *     /
     *    3
     *   /
     *  2
     * /
     * 1
     */
    tree = btree_create();
    node1 = create_node(4);
    node2 = create_node(3);
    node3 = create_node(2);
    node4 = create_node(1);
    
    tree->root = node1;
    node1->left = node2;
    node2->left = node3;
    node3->left = node4;
    
    node = btree_get_first_same_parent_order(tree,node4,node2);
    CU_ASSERT(node==node2);
    
    btree_free(tree);
    
    /**     1
     *       \
     *        2
     *         \
     *          3
     *           \
     *            4
     */
    tree = btree_create();
    node1 = create_node(1);
    node2 = create_node(2);
    node3 = create_node(3);
    node4 = create_node(4);
    
    tree->root = node1;
    node1->right = node2;
    node2->right = node3;
    node3->right = node4;
    
    node = btree_get_first_same_parent_order(tree,node4,node2);
    CU_ASSERT(node==node2);
    
    btree_free(tree);
    
    
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("ut_btree", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
//    (NULL == CU_add_test(pSuite, "testBtree_get_depth", testBtree_get_depth)) ||
//            (NULL == CU_add_test(pSuite, "testBtree_is_balance", testBtree_is_balance))||
//            (NULL == CU_add_test(pSuite,"testBtree_is_balance_v1",testBtree_is_balance_v1))||
    
    if ((NULL == CU_add_test(pSuite,"testBtree_get_first_same_parent",testBtree_get_first_same_parent))||
            (NULL == CU_add_test(pSuite,"testBtree_get_frist_same_parent_order",testBtree_get_frist_same_parent_order))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
