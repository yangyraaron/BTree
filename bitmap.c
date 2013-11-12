#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define BITMAP_LEN 32
#define SHIFT 5
#define MASK 0x1F
#define BIT 0x01

int* bp_create(int size) {
    int* bitmap = (int*) calloc(size,sizeof(int));
    assert(NULL != bitmap);

    return bitmap;
}       

void bp_free(int* bp) {
    free(bp);
}

void bp_set(int* bp, int value) {
    int index = value / BITMAP_LEN;
    int bit = bp[index];

    int pos = value % BITMAP_LEN;
    bp[index] = bit | (BIT << pos);

    //printf("\n after set value is %d \n",  bp[index]);
}

int bp_test(int* bp, int value) {
    int index = (value >> SHIFT);
    int bit = bp[index];

    int pos = value & MASK;
    return bit & (BIT << pos);
}

void bp_clear(int* bp, int value) {
    int index = value / BITMAP_LEN;
    int bit = bp[index];

    int pos = value % BITMAP_LEN;

    bp[index] = bit & (~(BIT << pos));

    //printf("\n after clear value is %d \n", bp[index]);
}