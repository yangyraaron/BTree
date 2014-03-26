
#include <assert.h>
#include <stdlib.h>
#include "gc.h"

VM* createVM(){
    VM* vm = (VM*) malloc(sizeof(VM));
    assert(NULL!=vm);
    
    vm->stackSize=0;
    vm->numObjects=0;
    vm->maxObjects = INITIAL_GC_THRESHOLD;
    return vm;
}

void pushToVM(VM* vm,Object* value){
    assert(vm->stackSize<STACK_MAX);
    vm->stack[vm->stackSize++] = value;
}

Object* popFromVM(VM* vm){
    assert(vm->stackSize>0);
    return vm->stack[--vm->stackSize];
}

Object* newObject(VM* vm,ObjectType type){
    if (vm->numObjects == vm->maxObjects) gc(vm);
    
    Object* obj = (Object*) malloc(sizeof(Object));
    obj->type = type;
    obj->marked = 0;
    
    //insert the new object into list head
    obj->next = vm->head;
    vm->head = obj;
    vm->numObjects++;
    
    return obj;
}

void pushInt(VM* vm,int value){
    Object* obj = newObject(vm,OBJ_INT);
    obj->value = value;
    pushToVm(vm,obj);
}

Object* pushPair(VM* vm){
    Object* pair = newObject(vm,OBJ_PAIR);
    pair->tail = popFromVM(vm);
    pair->head = popFromVM(vm);
    pushToVm(vm,pair);
    
    return pair;
}

static void mark(Object* obj){
    obj->marked=1;
    
    if(obj->marked) return;
    
    if(obj->type == OBJ_PAIR){
        mark(obj->head);
        mark(obj->tail);
    }
}

void markAll(VM* vm){
    int i;
    for(i=0;i<vm->stackSize;i++){
        mark(vm->stack[i]);
    }
}

void sweep(VM* vm){
    Object** node = &vm->head;
    while(*node){
        if(!(*node)->marked){
            Object* unreached = *node;
            //the address stored object reset to next element
            *node = unreached->next;
            
            free(unreached);
        }else{
            (*node)->marked=0;
            node = &(*node)->next;
        }
    }
}

void gc(VM* vm){
    int numObjects = vm->numObjects;
    
    markAll(vm);
    sweep(vm);
    
    vm->maxObjects = numObjects*2;
}