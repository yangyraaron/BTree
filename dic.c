#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "dic.h"

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

static dic_entity_p create_entity(int key,void* value){
    dic_entity_p entity = (dic_entity_p)malloc(sizeof(dic_entity));
    assert(NULL!=entity);
    entity->key = key;
    entity->value = value;
    entity->next = NULL;
    
    return entity;
}

static void free_entity(dic_entity_p entity){
     if(NULL == entity) return;
    
    entity->next = NULL;
    free(entity);
}

dic_p dic_create(int size){
    dic_p dic = (dic_p) malloc(sizeof(dic));
    assert(NULL!=dic);
    
    dic->size = size;
    
    int head_size = next_prime(size);
    dic->heads = (dic_entity_p*) calloc(head_size,sizeof(dic_entity_p));
    
    return dic;
}

void dic_free(dic_p dic){
    int i;
    dic_entity_p entity = NULL;
    
    for(i=0;i<dic->size;++i){
        entity = dic->heads[i];
        
        if(NULL==entity) continue;
        
        while(NULL!=entity->next){
            dic->heads[i] = entity->next;
            free_entity(entity);
            entity = dic->heads[i];
        }
        
        free_entity(entity);
    }
    
    dic->size = 0;
    free(dic->heads);
    free(dic);
}

void dic_add(dic_p dic,int key,void* value){
    dic_entity_p entity = create_entity(key,value);
    
    int index = key%dic->size;
    dic_entity_p head = dic->heads[index];
    if(NULL == head){
        dic->heads[index] = entity;
    }else{
        dic_entity_p node = head;
        while(NULL!=node->next){
            node = node->next;
        }
        node->next = entity;
    }
}

void* dic_get(dic_p dic,int key){
    int index = key%dic->size;
    dic_entity_p node = dic->heads[index];
    while(NULL!=node){
        if(node->key == key)
            return node->value;
        node = node->next;
    }
    
    return NULL;
    
}
