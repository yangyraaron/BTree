/* 
 * File:   heap.h
 * Author: wisedulab2
 *
 * Created on November 25, 2013, 9:33 AM
 */

#ifndef HEAP_H
#define	HEAP_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MIN_KEY -1000000
    
    //typedef struct heap_elements_s* heap_element_p;
    typedef struct heap_element_s{
        int key;
        void* value;
    }heap_element,*heap_element_p;
    
    typedef struct heap_s{
        unsigned int max_heap_size;
        unsigned int size;
        heap_element_p* elements;
        
    }heap,*heap_p;
    
    heap_p pq_create(unsigned int);
    void pq_free(heap_p);
    void pq_insert(heap_p,int,void*);
    void* pq_pop(heap_p);

#ifdef	__cplusplus
}
#endif

#endif	/* HEAP_H */

