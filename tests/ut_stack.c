/*
 * File:   ut_stack.c
 * Author: aaron
 *
 * Created on 2013-11-1, 21:43:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "stack.h"

/*
 * CUnit Test Suite
 */

char* str_arr[]={"test1","test2"};
int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testStack_push() {
    stack_p stack = stack_create();
    CU_ASSERT(stack!=NULL);
    
    stack_push(stack,&str_arr[0]);
    CU_ASSERT(stack->size==1);
    
    stack_push(stack,&str_arr[1]);
    CU_ASSERT(stack->size==2);
    
    char* str = (char*)stack_pop(stack);
    CU_ASSERT(strcmp(str,str_arr[0]));
    
    str = (char*)stack_pop(stack);
    CU_ASSERT(strcmp(str,str_arr[1]));
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("ut_stack", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testStack_push", testStack_push))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
