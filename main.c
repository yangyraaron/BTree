/* 
 * File:   main.c
 * Author: wisedulab2
 *
 * Created on October 28, 2013, 3:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
//#include "btree.h"
#include "skiplist.h"
/*
 * 
 */

//extern void btree_pef_balance_test(int);


int main(int argc, char** argv) {
    //int number = 32768*256;
    
    //printf("int size %ld",sizeof(int));
    //btree_pef_balance_test(number);
    //btree_pef_balance_v1_test(number);
    
//    int value = 100;
//    int time = value/32;
//    int time1 = value>>5;
//    
//    
//    printf("time : %d time1 : %d",time,time1);
    
    skiplist_p list = skip_create();
    
    int i;
    for(i=100;i>0;--i){
        skip_add(list,i);
    }
    
    skip_print(list);
    
    skip_free(list);
    
    return (EXIT_SUCCESS);
}

