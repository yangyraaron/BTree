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
extern void huf_compress(void);
extern void huf_uncompress(void);
extern void huf_word_compress(void);
extern void huf_word_uncompress(void);

int main(int argc, char** argv) {
    printf("compressing...\n");
    huf_compress();;
    printf("uncompress...\n");
    huf_uncompress();
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
    
//    skiplist_p list = skip_create();
//    
//    int i;
//    for(i=100;i>0;--i){
//        skip_add(list,i);
//    }
//    
//    skip_print(list);
//    
//    skip_free(list);
//    
//    list = skip_create();
//    for(i=1;i<101;++i){
//        skip_add(list,i);
//    }
//    skip_print(list);
//    
//    skip_free(list);
    
//    printf("int %ld\n",sizeof(unsigned int));
//    printf("long %ld\n",sizeof(unsigned long));
    
    
    return (EXIT_SUCCESS);
}

