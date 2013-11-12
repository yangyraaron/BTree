
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#include "set.h"

static void free_entity(set_entity_p);
static set_entity_p create_entity(int);

static int is_prime(int num){    
    if(num%2==0)
        return 0;
    
    int end_num = sqrt(num);
    int i;
    for (i=3; i<=end_num; i+=2) {
        if(num%i==0)
            return 0;
    }
    
    return 1;
}

static int next_prime(int num){
    
    if (num%2==0) {
        num+=1;
    }
    
    while (!is_prime(num)) {
        num+=2;
    }
    
    return num;
}

set_p set_create(int size){
    int prime = next_prime(size);
    set_p set = (set_p) malloc(sizeof(set));
    assert(NULL!=set);
    
    set->size = prime;
    set->heads = (set_entity_p*)calloc(sizeof(set_entity_p),set->size);
    
    return set;
}

void set_free(set_p set){
    int i;
    set_entity_p entity = NULL;
    
    for(i=0;i<set->size;++i){
        entity = set->heads[i];
        
        if(NULL==entity) continue;
        
        while(NULL!=entity->next){
            set->heads[i] = entity->next;
            free_entity(entity);
            entity = set->heads[i];
        }
        
        free_entity(entity);
    }
    
    set->size = 0;
    free(set->heads);
    free(set);
}

static void free_entity(set_entity_p entity){
    if(NULL == entity) return;
    
    entity->next = NULL;
    free(entity);
}

static set_entity_p create_entity(int key){
    set_entity_p entity = (set_entity_p) malloc(sizeof(set_entity));
    entity->key = key;
    entity->next = NULL;
    
    return entity;
}
void set_set(set_p set,int key){
    int index = key%set->size;
    
    set_entity_p head = set->heads[index];
    
    if(NULL == head)
        set->heads[index] = create_entity(key);
    else{
        set_entity_p node = head;
        
        while(NULL!=node->next){
            node = node->next;
        }
        node->next = create_entity(key);
    }
}

int set_get(set_p set,int key){
    int index = key%set->size;
    
    set_entity_p head = set->heads[index];
    if(head==NULL) return -1;
    
     set_entity_p node = head;
        
     while(NULL!=node->next){
         if(node->key == key)
             return key;
        node = node->next;
     }
     
     return node->key;
}