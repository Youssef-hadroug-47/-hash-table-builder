
typedef struct{
    char* key;
    char* value;
} ht_item;

typedef struct{
    int size;
    int count;
    ht_item** items; 

}ht_hash_table ;


void free_ht (ht_hash_table* ht);
ht_hash_table* ht_new ();
