/*
 * File:   ut_heap.c
 * Author: wisedulab2
 *
 * Created on Nov 25, 2013, 11:17:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "heap.h"

/*
 * CUnit Test Suite
 */

typedef struct row_s {
    int key;
    char* value;
} row, *row_p;

typedef struct table_s {
    row_p* rows;
    unsigned int len;
} table, *table_p;

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testPq_pop() {
    heap_p heap = pq_create(10);

    pq_insert(heap, 10, "test10");
    pq_insert(heap, 1, "test1");
    pq_insert(heap, 101, "test101");
    pq_insert(heap, 3, "test3");
    CU_ASSERT(heap->size == 4);

    char* value = (char*) pq_pop(heap);
    CU_ASSERT(strcmp(value, "test1") == 0);
    CU_ASSERT(heap->size == 3);
    value = (char*) pq_pop(heap);
    CU_ASSERT(strcmp(value, "test3") == 0);
    CU_ASSERT(heap->size == 2);
    value = (char*) pq_pop(heap);
    CU_ASSERT(strcmp(value, "test10") == 0);
    CU_ASSERT(heap->size == 1);

    pq_insert(heap, 5, "test5");
    CU_ASSERT(heap->size == 2);
    value = (char*) pq_pop(heap);
    CU_ASSERT(strcmp(value, "test5") == 0);

    pq_free(heap);

}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("ut_heap", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testPq_pop", testPq_pop))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
