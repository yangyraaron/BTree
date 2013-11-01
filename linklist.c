
#include <assert.h>
#include <stdlib.h>
#include "linklist.h"

static LINK_NODE create_node(void*);

LINK_LIST lk_list_create(){
    LINK_LIST list = (LINK_LIST) malloc(sizeof(link_list));
    assert(list!=NULL);
    
    list->head=NULL;
    list->tail=NULL;
    list->size=0;
    
    return list;
}

void lk_list_free(LINK_LIST list){
    lk_list_empty(list);
    
    free(list);
    list=NULL;
}

void lk_list_append(LINK_LIST list,void* value){
    if(list->size==0){
        LINK_NODE head = create_node(value);
        list->head=list->tail = head;
        list->tail->next = head;
    }else{
        LINK_NODE node = create_node(value);
        list->tail->next = node;
        list->tail=node;
        list->tail->next=list->head;
    }
    list->size++;
}

void* lk_list_pop(LINK_LIST list){
    if(list->size==0)
        return NULL;
    
    LINK_NODE node = list->head;
    void* value = node->value;
    
    if(list->size==1){
        list->head=list->tail=NULL;
    }else{
        list->head = node->next;
        list->tail->next = list->head;
    }
    
    list->size--;
    
    node->value=NULL;
    node->next=NULL;
    free(node);
    
    return value;
}

void lk_list_empty(LINK_LIST list){
    while(list->size>0){
        lk_list_pop(list);
    }
}

static LINK_NODE create_node(void* value){
    LINK_NODE node = (LINK_NODE) malloc(sizeof(link_node));
    node->next = NULL;
    node->value = value;
    
    return node;
}