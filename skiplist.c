
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "skiplist.h"

#define MAX_LEVEL 15

static skip_node_p create_node(int level, int key) {
    skip_node_p node = (skip_node_p) malloc(sizeof (skip_node) + (level+1) * sizeof (skip_node_p));
    assert(NULL != node);

    node->key = key;

    return node;
}

static int random_level() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL)
        level++;

    return level;
}

skiplist_p skip_create() {
    skiplist_p skiplist = (skiplist_p) malloc(sizeof (skiplist));
    assert(NULL != skiplist);

    skiplist->header = create_node(MAX_LEVEL, 0);
    skiplist->level = 0;

    int i;
    for (i = 0; i < MAX_LEVEL; ++i) {
        skiplist->header->forwards[i] = NULL;
    }

    return skiplist;
}

void skip_free(skiplist_p skiplist) {
    skip_node_p node = skiplist->header->forwards[0];
    skip_node_p tmp = NULL;
    while (NULL != node) {
        tmp = node;
        node = node->forwards[0];

        free(tmp);
    }
    
    free(skiplist->header);
    free(skiplist);
}

void skip_add(skiplist_p skiplist, int value) {
    int i;
    //the array contains the nodes in every level needs to be updated
    skip_node_p updates[MAX_LEVEL];
    skip_node_p node = skiplist->header;
    for (i = skiplist->level; i >= 0; --i) {
        while ((NULL != node->forwards[i]) && (node->forwards[i]->key < value)) {
            node = node->forwards[i];
        }

        updates[i] = node;
    }

    int level = random_level();
    skip_node_p cur_node = create_node(level, value);
    //create the list that isn't created
    if (level > skiplist->level) {
        for (i = level; i > skiplist->level; --i) {
            updates[i] = skiplist->header;
        }

        skiplist->level = level;
    }
    //update the nodes and insert current node
    for (i = 0; i <= level; ++i) {
        cur_node->forwards[i] = updates[i]->forwards[i];
        updates[i]->forwards[i] = cur_node;
    }

}

void skip_del(skiplist_p skiplist, int value) {
    int i;
    skip_node_p updates[MAX_LEVEL];
    skip_node_p node = skiplist->header;
    skip_node_p last = NULL;

    for (i = skiplist->level; i >= 0; --i) {
        while ((last = node->forwards[i]) && last->key < value) {
            node = last;
        }

        updates[i] = node;
    }

    /*because the last node value is in the bottom level list
     * so if the node is null or key is not equal to value then 
     * there is no value in the list
     *  */
    if (last && last->key == value) {
        for (i = skiplist->level; i >= 0; --i) {
            if (updates[i]->forwards[i] == last) {
                updates[i]->forwards[i] = last->forwards[i];
            }

            if (NULL == skiplist->header->forwards[i]) {
                skiplist->level--;
            }
        }
        free(last);
    }
}

int skip_test(skiplist_p skiplist, int value) {
    int i;
    skip_node_p node = skiplist->header;

    for (i = skiplist->level; i >= 0; --i) {
        while ((NULL != node->forwards[i]) && (node->forwards[i]->key <= value)) {
            if (value == node->key) return 1;

            node = node->forwards[i];
        }
    }

    //if the node is the last node in the bottom level
    if (node->key == value) return 1;

    return 0;
}

void skip_print(skiplist_p skiplist) {
    skip_node_p node = NULL;
    int i,j;

    printf("\n");

    for (i = skiplist->level,j=0; i >= 0; --i) {
        node = skiplist->header->forwards[i];

        printf("Level:%d ", i);
        while (NULL != node) {
            printf("%d-->", node->key);
            node = node->forwards[i];
            ++j;
        }
        printf("NULL | total:%d\n",j);

    }
}