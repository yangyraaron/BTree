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
    btree_pef_balance_test(32768*256);
    
    return (EXIT_SUCCESS);
}

