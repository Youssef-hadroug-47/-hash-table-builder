#include "hash_table.h"
#include "prime.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 


static ht_item* ht_new_item (const char* k, const char*v){
    ht_item* new_item = (ht_item*)malloc(sizeof(ht_item));
    int attempt = 0;
    while(!new_item && attempt < MAX_ALLOCATION_ATTEMPT){
        attempt++;
        new_item = (ht_item*)malloc(sizeof(ht_item));
    }
    if (!new_item)
        return NULL;
    
    new_item->key = k ? strdup(k) : NULL;
    new_item->value = v ? strdup(v) : NULL;
    return new_item;
}


ht_hash_table* ht_new (int size){
    ht_hash_table* new_ht = (ht_hash_table*) malloc (sizeof(ht_hash_table));
    if (!new_ht)
        return NULL;
    new_ht->size = size;
    new_ht->count = 0;
    ht_item** items_bucket = (ht_item**) calloc((size_t)new_ht->size , sizeof(ht_item*));
    int attempt = 0;
    while(!items_bucket && attempt < MAX_ALLOCATION_ATTEMPT){
        attempt++;
        items_bucket = (ht_item**) calloc((size_t)new_ht->size , sizeof(ht_item*));
    }
    if (!items_bucket){
        free(new_ht);
        return NULL;
    }
    new_ht->items = items_bucket;
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
    for (int i=0 ;i<ht->size ;i++)
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
        hash += (long)(pow(prime, (len - (i+1)))) * char_code;
    }
    hash %= size;
    return (int)hash;
}

int get_hash(const char *key , int attempt, int size) {
    int hash_a = hash(key,PRIME_1,size);
    int hash_b = hash(key,PRIME_2,size);
    return (hash_a + attempt * (hash_b + 1)) % size;
}

static int search_key (ht_hash_table* ht , const char* key) {
    int attempt = 0;
    ht_item* index ;
    int hash_res ;

    do {
        hash_res = get_hash(key, attempt, ht->size);
        printf("hash code %d\n",hash_res);
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


int ht_insert(ht_hash_table *ht, const char *key, const char *value) {
    ht_item* temp = ht_new_item(key,value);
    if (!temp)
        return 0;
    int size_ratio = ((float)ht->count/ht->size) * 100;

    if (size_ratio > SIZE_RATIO){
        printf("Resizing started ...\r\n");
        if (ht_resize(ht))
            printf("Resizing completed successfully with new_size %d\r\n",ht->size);
        else 
            printf("Resizing failed\r\n");
    } 
    printf("key search started\r\n");     
    int hash_index = search_key(ht,key);
    printf("key search finished\r\n");
    if (ht->items[hash_index]){
        free_ht_item(ht->items[hash_index]);
    }
    else 
        ht->count++;
    ht->items[hash_index] = temp;
    return 1;
    
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


int ht_resize(ht_hash_table* ht){
    int tmp_size = ht->size * NEW_SIZE_COEFF;
    int new_size = next_prime(tmp_size);
    
    ht_item** temp = realloc(ht->items, new_size * sizeof(ht_item*));
    if (!temp) return 0;
    ht->items = temp;

    memset(ht->items+ht->size,0,(new_size - ht->size)*sizeof(ht_item*));
    // Debug
    // int count = 0;
    // for (int i = 0 ;i<new_size; i++)
        // if (ht->items[i+1]) count++;
    // printf("The number of Non NULL items is %d\n",count);
    // printf("old Capacity %d , New Capacity %d\r\n",ht->size,new_size);

    ht->size = new_size;
    return 1; 
}
