/*
 * File:   ut_dic.c
 * Author: wisedulab2
 *
 * Created on Nov 26, 2013, 11:57:41 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "dic.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testDic_add() {
    dic_p dic = dic_create(256);
    
    dic_add(dic,100,"abc");
    dic_add(dic,66,"bcd");
    
    char* value = (char*) dic_get(dic,100);
    CU_ASSERT(strcmp(value,"abc")==0);
    value = (char*) dic_get(dic,66);
    CU_ASSERT(strcmp(value,"bcd")==0);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("ut_dic", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testDic_add", testDic_add))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
