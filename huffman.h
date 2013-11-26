/* 
 * File:   huffman.h
 * Author: wisedulab2
 *
 * Created on November 25, 2013, 2:27 PM
 */

#ifndef HUFFMAN_H
#define	HUFFMAN_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct huf_node_s* huf_node_p;
    
    typedef struct huf_node_s {
        unsigned int weight;
        char* value;
        char* encoding;
        huf_node_p parent;
        huf_node_p left;
        huf_node_p right;
        huf_node_p next;
    } huf_node;

    typedef struct huf_s {
        unsigned int size;
        huf_node_p root;
        huf_node_p leaf_head;
        huf_node_p leaf_tail;

    } huf, *huf_p;
    
    
    typedef struct encoding_map_s{
        huf_node_p* maps;
        unsigned int len;
    }encoding_map,*encoding_map_p;

    void huf_add_key(unsigned int, char*);
    huf_p huf_create(void);
    encoding_map_p huf_create_maps(huf_p);
    void huf_free(huf_p);

#ifdef	__cplusplus
}
#endif

#endif	/* HUFFMAN_H */

