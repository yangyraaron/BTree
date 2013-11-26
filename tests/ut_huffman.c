/*
 * File:   ut_huffman.c
 * Author: wisedulab2
 *
 * Created on Nov 25, 2013, 6:12:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "huffman.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testHuf_create_maps() {
    huf_add_key(12, "a");
    huf_add_key(40, "b");
    huf_add_key(15, "c");
    huf_add_key(8, "d");
    huf_add_key(25, "e");

    huf_p huf = huf_create();
    encoding_map_p encoding = huf_create_maps(huf);
    CU_ASSERT(encoding->len == 5);
    CU_ASSERT(strcmp(encoding->maps[0]->encoding, "1110")==0);
    CU_ASSERT(strcmp(encoding->maps[1]->encoding, "1111")==0);
    CU_ASSERT(strcmp(encoding->maps[2]->encoding, "110")==0);
    CU_ASSERT(strcmp(encoding->maps[3]->encoding, "10")==0);
    CU_ASSERT(strcmp(encoding->maps[4]->encoding, "0")==0);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("ut_huffman", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testHuf_create_maps", testHuf_create_maps))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
