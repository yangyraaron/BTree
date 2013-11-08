/*
 * File:   ut_set.c
 * Author: wisedulab2
 *
 * Created on Nov 8, 2013, 4:25:59 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "set.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testSet_get() {
    set_p set = set_create(100);
    
    int numbers[100];
    int i,j;
    for(i=0;i<100;++i){
        numbers[i] = rand();
        set_set(set,numbers[i]);
    }
    
    for(i=0;i<100;++i){
        j = set_get(set,numbers[i]);
        //printf("key is %d \n",j);
        CU_ASSERT(j!=-1);
    }
    
    set_free(set);
}

void testSet_set() {
//    set_p set;
//    int key;
//    set_set(set, key);
//    if (1 /*check result*/) {
//        CU_ASSERT(0);
//    }
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("ut_set", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testSet_get", testSet_get)) ||
            (NULL == CU_add_test(pSuite, "testSet_set", testSet_set))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
