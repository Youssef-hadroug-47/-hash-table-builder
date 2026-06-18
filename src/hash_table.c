#include "hash_table.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 


static ht_item* ht_new_item (const char* k, const char*v){
    ht_item* new_item = (ht_item*)malloc(sizeof(ht_item));
    new_item->key = strdup(k);
    new_item->value = strdup(v);
    return new_item;
}


ht_hash_table* ht_new (){
    ht_hash_table* new_ht = (ht_hash_table*) malloc (sizeof(ht_hash_table));
    
    new_ht->size = SIZE;
    new_ht->count = 0;
    new_ht->items = (ht_item**) calloc((size_t)new_ht->size , sizeof(ht_item*));

    return new_ht;
}


static ht_item HT_DELETED_ITEM = {NULL,NULL};
static void free_ht_item (ht_item* item) {
    if (!item || item == &HT_DELETED_ITEM) return;
    if (item->value) free(item->value);
    if (item->key) free(item->key);
    free(item);
}

void free_ht (ht_hash_table* ht) {
    for (int i=0 ;i<ht->count ;i++)
        if (ht->items[i])
            free_ht_item(ht->items[i]);
    free(ht->items);
    free(ht);
}

int hash(const char* key , int prime , int size){
    long hash = 0;
    const int len = strlen(key);
    for (int i=0; i<len ; i++) {
        int char_code = key[i];
        hash += (pow(prime, (len - (i+1)))) * char_code;
    }
    hash %= size;
    return (int)hash;
}

int get_hash(const char *key , int attempt) {
    int hash_a = hash(key,PRIME_1,SIZE);
    int hash_b = hash(key,PRIME_2,SIZE);
    return (hash_a + attempt * (hash_b + 1) + 1) % SIZE;
}

static int search_key (ht_hash_table* ht , const char* key) {
    int attempt = 0;
    ht_item* index ;
    int hash_res ;

    do {
        hash_res = get_hash(key, attempt);
        index = ht->items[hash_res];
        if (index){
            attempt++;
            if (index == &HT_DELETED_ITEM || !strcmp(index->key,key)){
                break;
            }
        }
    } while (index);
    return hash_res ;   
    
}


void ht_insert(ht_hash_table *ht, const char *key, const char *value) {
    int hash_index = search_key(ht,key);
    if (ht->items[hash_index]){
        free_ht_item(ht->items[hash_index]);
    }
    else 
        ht->count++;
    ht->items[hash_index] = ht_new_item(key,value);

}

char* ht_search(ht_hash_table *ht, const char *key){
    int hash_index = search_key(ht,key);
    

    ht_item* item = ht->items[hash_index];
    return (item && item != &HT_DELETED_ITEM) ? item->value : NULL ;
}

void ht_delete(ht_hash_table *ht, const char *key){
    int hash_index = search_key(ht, key);
    free_ht_item(ht->items[hash_index]);
    ht->items[hash_index] = &HT_DELETED_ITEM;
    ht->count--;
}



