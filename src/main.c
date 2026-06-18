#include "hash_table.h"
#include <stdio.h>

int main(int count , char** args){
    

    printf("Welcome to my Hash Table builder ");
    ht_hash_table* hash_table = ht_new();
    free_ht(hash_table);

    return 0;
}
