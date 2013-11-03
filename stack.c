#include <assert.h>
#include <stdlib.h>

#include "stack.h"

static stack_item_p create_item(void* value){
    stack_item_p item = (stack_item_p)malloc(sizeof(stack_item));
    assert(item!=NULL);
    
    item->value = value;
    item->next = NULL;
    
    return item;
}

static void free_item(stack_item_p item){
    if(item==NULL) return;
    
    item->next = NULL;
    item->value = NULL;
    
    free(item);
}

stack_p stack_create(){
    stack_p stack = (stack_p)malloc(sizeof(stack));
    assert(stack!=NULL);
    
    stack->head=NULL;
    stack->size = 0;
    
    return stack;
}

void stack_free(stack_p stack){
    if(stack == NULL) return ;
    
    while(stack->size>0)
        stack_pop(stack);
    
    stack->head = NULL;
    free(stack);
}

void stack_push(stack_p stack,void* value){
    if(stack==NULL) return;
    
    stack_item_p item = create_item(value);
    if(stack->head!=NULL){
        item->next = stack->head;
    }
    stack->head = item;
    stack->size++;
}

void* stack_pop(stack_p stack){
    if(stack==NULL) return NULL;
    
    if(stack->size==0) return NULL;
    
    stack_item_p item = stack->head;
    void* value = item->value;
    stack->head = stack->head->next;
    
    free_item(item);
    
    return value;
}
