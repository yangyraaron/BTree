
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "huffman.h"

#define TEST_FILE "/home/wisedulab2/NetBeansProjects/huftest.html"

typedef struct key_counter_s* key_counter_p;
typedef struct key_counter_s{
    int key;
    int counter;
    key_counter_p next;
}key_counter;

static key_counter_p create_counter(int key,int counter){
    key_counter_p kc = (key_counter_p)malloc(sizeof(key_counter));
    kc->key = key;
    kc->counter = counter;
    
    return kc;
}

static key_counter_p get_counter(key_counter_p map,int key){
    key_counter_p node = map;
    while(NULL!=node){
        if(key == node->key)
            return node;
        node = node->next;
    }
    
    return NULL;
}

static key_counter_p counter_map;
static key_counter_p last_counter;
static huf_p huff;
static encoding_map_p en_map;

static void readFile(char* path){
    FILE* file = fopen(path,"r");
    assert(NULL!=file);
    
    int c;
    do{
        c = fgetc(file);
        if(NULL == counter_map){
            counter_map = create_counter(c,1);
            last_counter = counter_map;
        }else{
            key_counter_p counter = get_counter(counter_map,c);
            if(NULL==counter){
                counter = create_counter(c,1);
                last_counter->next = counter;
                last_counter = counter;
            }else{
                ++counter->counter;
            }
        }
    }
    while(EOF!=c);
    
    fclose(file);
}

static void compress_encoding(char* path){
    readFile(path);
    
    key_counter_p node = counter_map;
    while(NULL!=node){
        char* value = (char*)malloc(sizeof(node->key));
        memcpy(value,&node->key,sizeof(node->key));
        
        huf_add_key(node->counter,value);
        
        node=node->next;
    }
    
    huff = huf_create();
    en_map= huf_create_maps(huff);
}

static char* get_encoding(int key){
    int i;
    i = en_map->len-1;
    
    while(i>=0){
        huf_node_p encoding = en_map->maps[i];
        if(((int)*encoding->value) == key){
            return encoding->encoding;
        }
        --i;
    }
    
    return NULL;
}

static char* generate_file(char* file){
    char* last = file+strlen(file)-1;
    while(*last!='.'){
        --last;
    }
    int ex_index = last-file;
    char* path = malloc((ex_index+4)*sizeof(char));
    memcpy(path,file,ex_index);
    strcat(path,".huff");
    
    return path;
}

void huf_compress(){
    compress_encoding(TEST_FILE);
    
    char* file = generate_file(TEST_FILE);
    FILE* orig_file = fopen(TEST_FILE,"r");
     FILE* des_file = fopen(file,"w");
     
    int c;
    //char* content=(char*)malloc(sizeof(char));
    unsigned int tmp=0xFF;
    char* encoding;
    int index=8;
    
    do{
        c = fgetc(orig_file);
        encoding = get_encoding(c);
        printf("char : %c\n",c);
        if(NULL==encoding) continue;
        
        
        int i;
        i=0;
        int len = strlen(encoding);
        while(i<len){
            char bit = *encoding;
            int value = bit=='0'?0x00:0x01;
            if(value==0)
                tmp = tmp&(~(~value<<(index-1)));
            
            ++i;
            ++encoding;
            index--;
            
            if(index==0){
                fputc(tmp,des_file);
                tmp = 0xFF;
                index=8;
            }
        }
        
    }while(EOF!=c);
    if(index!=0)
        fputc(tmp,des_file);
    
    fclose(orig_file);
    
    fclose(des_file);
}