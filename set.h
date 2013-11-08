/* 
 * File:   hashtable.h
 * Author: wisedulab2
 *
 * Created on November 8, 2013, 2:18 PM
 */

#ifndef SET_H
#define	SET_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct set_s* set_p;
    typedef struct set_entity_s* set_entity_p;

    typedef struct set_s {
        set_entity_p* heads;
        int size;
    } set;

    typedef struct set_entity_s {
        int key;
        set_entity_p next;
    } set_entity;

    
    set_p set_create(int);
    void set_set(set_p set,int key);
    int set_get(set_p set,int key);
    void set_free(set_p set);

#ifdef	__cplusplus
}
#endif

#endif	/* SET_H */

