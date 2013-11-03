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
BTREE_NODE btre_get_first_leaf(BTREE_NODE node);
int btree_get_depth_v1(BTREE);
int btree_is_balance_v1(BTREE);
void btree_add_left(BTREE_NODE ,BTREE_NODE );
void btree_add_right(BTREE_NODE ,BTREE_NODE );
BTREE_NODE btree_get_first_same_parent(BTREE_NODE,BTREE_NODE);

#ifdef	__cplusplus
}
#endif

#endif	/* BTREE_H */

