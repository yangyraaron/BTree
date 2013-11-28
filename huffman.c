#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "heap.h"

#define MAX_ELEMENTS 100000

static heap_p key_heap;

static huf_node_p create_node(unsigned int weight, void* value) {
    huf_node_p node = (huf_node_p) malloc(sizeof (huf_node));
    node->weight = weight;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->next = NULL;
    node->encoding = NULL;

    return node;
}

static huf_node_p get_next_node() {
    if (key_heap->size == 0)
        return NULL;

    return (huf_node_p) pq_pop(key_heap);
}

void huf_add_key(unsigned int weight, void* value) {
    if (NULL == key_heap)
        key_heap = pq_create(MAX_ELEMENTS);

    huf_node_p node = create_node(weight, value);

    pq_insert(key_heap, weight, node);
}

huf_p huf_create() {
    huf_node_p min1 = NULL, min2 = NULL;

    huf_p h = (huf_p) malloc(sizeof (huf));
    h->leaf_head = NULL;
    h->leaf_tail = NULL;
    h->size = key_heap->size;

    while (1) {
        min1 = get_next_node();
        if (NULL == min1) break;

        min2 = get_next_node();
        if (NULL == min2) break;

        //when the node is leaf node
        if ((NULL == min1->left) && (NULL == min1->right)) {
            if (NULL == h->leaf_head)
                h->leaf_head = h->leaf_tail = min1;
            else {
                h->leaf_tail->next = min1;
                h->leaf_tail = min1;
            }
        }

        if ((NULL == min2->left) && (NULL == min2->right)) {
            h->leaf_tail->next = min2;
            h->leaf_tail = min2;
        }

        huf_node_p parent = create_node(min1->weight + min2->weight, NULL);
        if (min1->weight <= min2->weight) {
            //this code is very important because if the weight is same you may not find correct value
            if(min1->weight == min2->weight)
                --min1->weight;
            parent->left = min1;
            parent->right = min2;
        } else {
            parent->left = min2;
            parent->right = min1;
        }
        min1->parent = parent;
        min2->parent = parent;

        pq_insert(key_heap, parent->weight, parent);
    }

    h->root = min1;

    return h;
}

static void strreverse(char* str) {
    char* head = str;
    char* last = str + strlen(str) - 1;
    char tmp = NULL;
    while (head < last) {
        tmp = *head;
        *head = *last;
        *last = tmp;

        head++;
        last--;
    }
}

static char* caculate_path(huf_node_p node) {
    char* path = (char*) calloc(2,sizeof(char));
    
    while (NULL != node->parent) {
       
        char* value;
        if (node->weight < node->parent->right->weight)
            value ="0";
        else
            value ="1";

        if (strcmp(path, "") != 0) {
            path = realloc(path, strlen(path) + 1);
            strcat(path,value);
        }else
        {
            *path = *value;
        }
        
        node = node->parent;
    }
    strreverse(path);

    return path;
}

encoding_map_p huf_create_maps(huf_p huf) {

    encoding_map_p encoding = (encoding_map_p) malloc(sizeof (encoding_map));
    encoding->maps = (huf_node_p*) malloc(huf->size * sizeof (huf_node_p));
    encoding->len = huf->size;

    huf_node_p node = huf->leaf_head;

    int i;
    for (i = 0; i < encoding->len; ++i) {
        node->encoding = caculate_path(node);
        encoding->maps[i] = node;
        node = node->next;
    }

    return encoding;
}

