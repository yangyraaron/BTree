/*
 * File:   ut_linklist.c
 * Author: wisedulab2
 *
 * Created on Oct 30, 2013, 1:23:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "linklist.h"
/*
 * CUnit Test Suite
 */

#define GET_INT(p)  *((int *)(p))

static int arr[]={1,2,3};

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testLk_list_append() {
    LINK_LIST list = lk_list_create();
    CU_ASSERT(list!=NULL);
    
    lk_list_append(list,&arr[0]);
    CU_ASSERT(list->size==1);
    CU_ASSERT(GET_INT(list->head->value)==1);
    CU_ASSERT(GET_INT(list->tail->value)==1);
    CU_ASSERT(list->tail->next==list->head);
    
    lk_list_append(list,&arr[1]);
    CU_ASSERT(list->size==2);
    CU_ASSERT(GET_INT(list->head->value)=1);
    CU_ASSERT(GET_INT(list->tail->value)==2);
    CU_ASSERT(list->tail->next==list->head);
    
    lk_list_free(list);
}


void testLk_list_pop() {
    LINK_LIST list = lk_list_create();
    CU_ASSERT(list!=NULL);
    
    lk_list_append(list,&arr[0]);
    lk_list_append(list,&arr[1]);
    lk_list_append(list,&arr[2]);
    
    int value1 =GET_INT(lk_list_pop(list));
    CU_ASSERT(value1=arr[0]);
    CU_ASSERT(list->size==2);
    CU_ASSERT(list->tail->next==list->head);
    
    int value2 =GET_INT(lk_list_pop(list));
    CU_ASSERT(value2=arr[1]);
    CU_ASSERT(list->size==1);
    CU_ASSERT(list->tail==list->head);
    
    int value3 =GET_INT(lk_list_pop(list));
    CU_ASSERT(value3=arr[2]);
    CU_ASSERT(list->size==0);
    CU_ASSERT(list->head==NULL);
    CU_ASSERT(list->tail==NULL);
    
    lk_list_free(list);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("ut_linklist", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testLk_list_append", testLk_list_append)) ||
            (NULL == CU_add_test(pSuite, "testLk_list_pop", testLk_list_pop))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
