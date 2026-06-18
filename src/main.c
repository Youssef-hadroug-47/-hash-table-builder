#include "hash_table.h"
#include <stdio.h>


int main(int count , char** args){
   
    
    printf("Welcome to my Hash Table builder :)\n");
    ht_hash_table* hash_table = ht_new();
    ht_insert(hash_table, "youssef", "hadroug");
    ht_insert(hash_table,"yahya","hadroug");
    ht_insert(hash_table,"youssef","saadallah");
    ht_delete(hash_table, "youssef");
    ht_insert(hash_table,"youssef","hadroug");

    for (int i=0; i<hash_table->size ;i++)
        if (hash_table->items[i] 
                && hash_table->items[i]->key 
                && hash_table->items[i]->value
            )
            printf("%s: %s\n",hash_table->items[i]->key , hash_table->items[i]->value);

    free_ht(hash_table);
    return 0;
}
