#include "hash_table.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>



static ht_item* ht_new_item (const char* k, const char*v){
    ht_item* new_item = (ht_item*)malloc(sizeof(ht_item));
    new_item->key = strdup(k);
    new_item->value = strdup(v);
    return new_item;
}


ht_hash_table* ht_new (){
    ht_hash_table* new_ht = (ht_hash_table*) malloc (sizeof(ht_hash_table));
    
    new_ht->size = 53;
    new_ht->count = 0;
    new_ht->items = (ht_item**) calloc((size_t)new_ht->size , sizeof(ht_item*));

    return new_ht;
}


static void free_ht_item (ht_item* item) {
    free(item->value);
    free(item->key);
    free(item);
    item = NULL;
}

void free_ht (ht_hash_table* ht) {
    for (int i=0 ;i<ht->count ;i++)
        if (ht->items[i])
            free_ht_item(ht->items[i]);
    free(ht->items);
    free(ht);
}
