/*
 * File:   ut_skiplist.c
 * Author: wisedulab2
 *
 * Created on Nov 12, 2013, 3:13:52 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "skiplist.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testSkip_test() {
    skiplist_p skiplist = skip_create();
    
    skip_add(skiplist,2);
    skip_add(skiplist,5);
    skip_add(skiplist,100);
    
    int value = skip_test(skiplist,2);
    CU_ASSERT(value==1);
    value = skip_test(skiplist,5);
    CU_ASSERT(value==1);
    value = skip_test(skiplist,100);
    CU_ASSERT(value==1);
    value = skip_test(skiplist,7);
    CU_ASSERT(value==0);
    
    skip_del(skiplist,5);
    value = skip_test(skiplist,5);
    CU_ASSERT(value==0);
    skip_del(skiplist,100);
    value = skip_test(skiplist,100);
    CU_ASSERT(value==0);
    
    skip_free(skiplist);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("ut_skiplist", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testSkip_test", testSkip_test))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
