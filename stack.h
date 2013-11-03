/* 
 * File:   stack.h
 * Author: aaron
 *
 * Created on 2013年11月1日, 下午8:48
 */

#ifndef STACK_H
#define	STACK_H

#ifdef	__cplusplus
extern "C" {
#endif
    typedef struct stack_s* stack_p;
    typedef struct stack_item_s* stack_item_p;
    typedef struct stack_s{
        stack_item_p head;
        int size;
    }stack;
    
    typedef struct stack_item_s{
        void* value;
        stack_item_p next;
    }stack_item;
    
    stack_p stack_create(void);
    void stack_free(stack_p);
    void stack_push(stack_p,void*);
    void* stack_pop(stack_p);

#ifdef	__cplusplus
}
#endif

#endif	/* STACK_H */

