/* 
 * File:   skiplist.h
 * Author: wisedulab2
 *
 * Created on November 12, 2013, 11:33 AM
 */

#ifndef SKIPLIST_H
#define	SKIPLIST_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct skip_node_s* skip_node_p;
    typedef struct skiplist_s* skiplist_p;
    
    typedef struct skip_node_s{
        int key;
        skip_node_p forwards[];
    }skip_node;
    
    typedef struct skiplist_s{
        int level;
        skip_node_p header;
    }skiplist;
    
    skiplist_p skip_create(void);
    void skip_free(skiplist_p);
    void skip_add(skiplist_p,int);
    int skip_test(skiplist_p,int);
    void skip_del(skiplist_p,int);

#ifdef	__cplusplus
}
#endif

#endif	/* SKIPLIST_H */

