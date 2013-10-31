/* 
 * File:   linklist.h
 * Author: wisedulab2
 *
 * Created on October 29, 2013, 3:42 PM
 * 
 *   
 * 
 */

#ifndef LINKLIST_H
#define	LINKLIST_H

#ifdef	__cplusplus
extern "C" {
#endif
    typedef struct link_node_s* LINK_NODE;
    typedef struct link_list_s* LINK_LIST;
    
    typedef struct link_list_s{
        LINK_NODE head;
        LINK_NODE tail;
        int size;
    }link_list;
    
    typedef struct link_node_s{
        void* value;
        LINK_NODE next;
    }link_node;


    LINK_LIST lk_list_create(void);
    void lk_list_append(LINK_LIST,void* value);
    void* lk_list_pop(LINK_LIST);
    void lk_list_free(LINK_LIST);
    void lk_list_empty(LINK_LIST);
    
#ifdef	__cplusplus
}
#endif

#endif	/* LINKLIST_H */

