#include "hash_table.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 53
#define MIN_PRINTABLE_ASCII 32
#define MAX_PRINTABLE_ASCII 126
#define STRING_LEN 5

int main(int count , char** args){
   
    
    printf("Welcome to my Hash Table builder :)\r\n");
    ht_hash_table* hash_table = ht_new(SIZE);
    int attempt = 0;
    while(!hash_table && attempt < MAX_ALLOCATION_ATTEMPT){
        attempt++;
        printf("Could not allocate memory for a hash_map\r\n");
        printf("Retrying..\r\n");
        hash_table = ht_new(SIZE);
    }
    if (!hash_table){
        printf("Unfortunately could not allocate memory for hash map\r\n");
        exit(1);
    }
    printf("Hash Map created succefully\r\n");
    srand(time(NULL));
    for (int i=0; i<1000; i++){
        

        printf("checking map memory..\r\n");
        int null_mem = 0;
        for(int j=0; j<hash_table->size; j++)
            if (!hash_table->items[j])  
                null_mem++;
        printf("%s\r\n",null_mem + hash_table->count == hash_table->size ?
                "All map memory is accessible" : "there is non-allocated memory"); 

        int rand_char;
        char rand_string[STRING_LEN+1];
        for(int j=0; j<STRING_LEN ;j++){
            rand_char = rand() % (1+MAX_PRINTABLE_ASCII-MIN_PRINTABLE_ASCII) + MIN_PRINTABLE_ASCII ;
            rand_string[j] = rand_char;
        }
        rand_string[STRING_LEN] = '\0';
        char string_len[5];
        sprintf(string_len, "%d", STRING_LEN); 
        printf("Inserting pair\r\n");
        int insert_res = ht_insert(hash_table, (const char*)rand_string ,string_len);
        if(!insert_res)
            printf("failed to insert %s: %s\r\n",rand_string,string_len);
        else
            printf("insertion completed successfully\r\n");
        // printf("elem inserted\n"); 
        printf("================================================\r\n");
    }
    // ht_insert(hash_table, "youssef", "hadroug");
    // ht_insert(hash_table,"yahya","hadroug");
    // ht_insert(hash_table,"youssef","saadallah");
    // ht_delete(hash_table, "youssef");
    // ht_insert(hash_table,"youssef","hadroug");

    // printf("Map capacity is %d\n",hash_table->size);

    // for (int i=0; i<hash_table->size ;i++)
    //     if (hash_table->items[i] 
    //             && hash_table->items[i]->key 
    //             && hash_table->items[i]->value
    //         )
    //         printf("%s: %s\n",hash_table->items[i]->key , hash_table->items[i]->value);

    free_ht(hash_table);
    return 0;
}
