#include "list.h"

typedef struct hash_table {
	List *buckets;
	unsigned int size;
} *HashTable;

HashTable initHashTable(unsigned int hash_size);

HashTable clear(HashTable hash_table);

HashTable eraseContent(HashTable hash_table);

HashTable add(HashTable hash_table, const char *c);

HashTable resize_double(HashTable old_table, const char *mode);

HashTable removeWord(HashTable hash_table, const char *c);

void print_bucket(HashTable hash_table, int index, const char *fileName);

void print(HashTable hash_table, const char *fileName);

void findEl(HashTable hash_table, const char *cuvant, const char *fileName);

HashTable callFunction(HashTable hash_table, char *cmd);

HashTable read(HashTable hash_table, char *argv[], int numOfFiles);

