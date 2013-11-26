#include <stdlib.h>
#include <assert.h>

#include "heap.h"

static int is_full(heap_p heap){
    if(heap->size==heap->max_heap_size)
        return 1;
    return 0;
}

static int is_empty(heap_p heap){
    return heap->size == 0;
}

heap_p pq_create(unsigned int max_elements) {
    assert(max_elements > 1);

    heap_p h = (heap_p) malloc(sizeof(heap));
    assert(NULL!= h);

    h->elements = (heap_element_p*) malloc(max_elements*sizeof (heap_element));
    assert(NULL != h->elements);

    h->max_heap_size = max_elements;
    h->size = 0;
    
    heap_element_p element = (heap_element_p) malloc(sizeof(heap_element));
    element->key = MIN_KEY;
    element->value = NULL;
    h->elements[0] = element;

    return h;
}

void pq_free(heap_p heap) {
    heap->max_heap_size = 0;
    heap->size = 0;

    int i;
    for (i = 0; i <= heap->size; ++i) {
        free(heap->elements[i]);
    }

    free(heap->elements);
    free(heap);
}

void pq_insert(heap_p heap, int key, void* value) {
    heap_element_p element = (heap_element_p) malloc(sizeof(heap_element));
    assert(NULL!=element);
    
    element->key = key;
    element->value = value;
    
    if(is_full(heap)) return;
    
    unsigned int i = ++heap->size;
    
    //because the first element in elements array is smallest, when i==1 then stop
    while(heap->elements[i/2]->key>key){
        heap->elements[i] = heap->elements[i/2];
        i/=2;
    }
    
    heap->elements[i] = element;
    
}
void* pq_pop(heap_p heap){
    if(is_empty(heap)) return NULL;
    
    unsigned int i,child;
    heap_element_p min_element,last_element;
    
    min_element = heap->elements[1];
    last_element = heap->elements[heap->size--];
    
    for(i=1;2*i<=heap->size;i=child){
        child = 2*i;
        if(child!=heap->size && heap->elements[child+1]->key<heap->elements[child]->key){
            child++;
        }
        
        if(last_element->key>heap->elements[child]->key)
            heap->elements[i] = heap->elements[child];
        else
            break;
    }
    heap->elements[i] = last_element;
    
    void * value = min_element->value;
    free(min_element);
    
    return value;
}
