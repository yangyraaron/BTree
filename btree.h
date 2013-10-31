/* 
 * File:   btree.h
 * Author: wisedulab2
 *
 * Created on October 28, 2013, 3:20 PM
 */

#ifndef BTREE_H
#define	BTREE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct btree_node_s* BTREE_NODE;
typedef struct btree_s* BTREE;
    
typedef struct btree_s{
    BTREE_NODE root;
} btree;

typedef struct btree_node_s{
    BTREE_NODE parent;
    int data;
    BTREE_NODE left;
    BTREE_NODE right;
} btree_node;

BTREE btree_create(void);
int btree_get_depth(BTREE);
int btree_is_balance(BTREE);
void btree_free(BTREE);

#ifdef	__cplusplus
}
#endif

#endif	/* BTREE_H */

