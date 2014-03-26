/* 
 * File:   gc.h
 * Author: aaron
 *
 * Created on 2014年3月26日, 上午11:40
 */

#ifndef GC_H
#define	GC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 10000
    
    typedef enum {
        OBJ_INT,
        OBJ_PAIR
    } ObjectType;

    typedef struct sobject {
        unsigned char marked;
        
        ObjectType type;

        union {
            int value;
            struct{
                struct sobject* head;
                struct sobject* tail;
            };
        };
        
        struct sobject* next;
    } Object;
    
    typedef struct{
        Object* head;
        
        Object* stack[STACK_MAX];
        int stackSize;
        int numObjects;
        int maxObjects;
    }VM;
    
    VM* createVM();
    void pushToVM(VM*, Object*);
    Object* popFromVM(VM*);
    Object* newObject(VM*,ObjectType);
    void pushInt(VM*,int);
    Object* pushPair(VM*);
    void markAll(VM*);
    void gc(VM*);
    
    



#ifdef	__cplusplus
}
#endif

#endif	/* GC_H */

