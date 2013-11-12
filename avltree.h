/* 
 * File:   avltree.h
 * Author: wisedulab2
 *
 * Created on November 11, 2013, 10:49 AM
 */

#ifndef AVLTREE_H
#define	AVLTREE_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct avltree_s* avltree_p;
    typedef struct avltree_node_s* avltree_node_p;
    
    typedef struct avltree_s{
        avltree_node_p root;
    }
    avltree;
    
    typedef struct avltree_node_s{
        int value;
        avltree_node_p left;
        avltree_node_p right;
        avltree_node_p parent;
    }avltree_node;

    
    avltree_p avltree_create(void);
    void avltree_free(avltree_p);
    void avltree_add(avltree_p tree,int value);
    void avltree_del(avltree_p tree,int value);
    void avltree_search(avltree_p tree,int value);
    

#ifdef	__cplusplus
}
#endif

#endif	/* AVLTREE_H */

