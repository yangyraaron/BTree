/* 
 * File:   dic.h
 * Author: wisedulab2
 *
 * Created on November 26, 2013, 11:27 AM
 */

#ifndef DIC_H
#define	DIC_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct dic_entity_s* dic_entity_p;
    
    typedef struct dic_entity_s {
        int key;
        void* value;
        dic_entity_p next;
    } dic_entity;

    typedef struct dic_s {
        dic_entity_p* heads;
        int size;
    } dic, *dic_p;

    dic_p dic_create(int);
    void dic_free(dic_p);
    void dic_add(dic_p, int, void*);
    void* dic_get(dic_p, int);


#ifdef	__cplusplus
}
#endif

#endif	/* DIC_H */

