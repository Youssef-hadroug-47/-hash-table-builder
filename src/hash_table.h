#ifndef HASH_TABLE

#define HASH_TABLE 

#define PRIME_1 151
#define PRIME_2 163
#define SIZE_RATIO 30
#define NEW_SIZE_COEFF 5/4
#define MAX_ALLOCATION_ATTEMPT 5

typedef struct{
    char* key;
    char* value;
} ht_item;

typedef struct{
    int size;
    int count;
    ht_item** items; 

}ht_hash_table ;


static ht_item* ht_new_item (const char* k, const char*v);
static void free_ht_item (ht_item* item);
ht_hash_table* ht_new (int size);
void free_ht (ht_hash_table* ht);
int hash(const char* key , int prime , int size);
int get_hash(const char*key, int attempt, int size);
int ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* ht, const char* key);
int ht_resize(ht_hash_table* ht);
#endif // !HASH_TABLE
