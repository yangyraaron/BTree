/* 
 * File:   main.c
 * Author: wisedulab2
 *
 * Created on October 28, 2013, 3:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
/*
 * 
 */

extern void btree_pef_balance_test(int);


int main(int argc, char** argv) {
    int number = 32768*256;
    
    //btree_pef_balance_test(number);
    btree_pef_balance_v1_test(number);
    
    return (EXIT_SUCCESS);
}

