/* 
 * File:   dictionary.h
 * Author: wisedulab2
 *
 * Created on November 19, 2013, 11:27 AM
 */

#ifndef DICTIONARY_H
#define	DICTIONARY_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct content_s* content_p;
    typedef struct dic_s* dic_p;
    
    typedef struct index_node_s{
        char* value;
        char* address;
    }index_node;
    
    typedef struct index_s{
        char* key;
        index_node** nodes;
        unsigned int length;
    }index;
    
    typedef struct index_table_s{
        index** indexs;
        unsigned int length;
        
    }index_table;
    
    
    typedef struct BNode_s{
        char* key[];
        char* address;
        int key_length;
        BNode* childs[];
        int childs_length;
    }BNode;
    
    typedef struct content_s{
        unsigned short position;
        unsigned short length;
    }content;

    typedef struct dic_s{
        char key_length;//1bytes
        char* content;//50bytes
        
        content_p pronounciation;//4bytes+4bytes=8bytes
        content_p explanation;
        content_p grammer;
        content_p examples;
        
        dic_p* synonyms;
        dic_p* antonyms;
        dic_p* word_groups;
        
    }dic;


#ifdef	__cplusplus
}
#endif

#endif	/* DICTIONARY_H */

