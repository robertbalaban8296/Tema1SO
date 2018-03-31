#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "hash_table.h"

int main(int argc, char **argv)
{
	unsigned int hash_size;
	HashTable hash_table = NULL;
	char *check = NULL;

	if (argc < 2) {
		fprintf(stderr, "Parametru invalid\n");
		exit(1);
	}
	hash_size = atoi(argv[1]);
	check = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 1));
	sprintf(check, "%d", hash_size);
	if (strcmp(check, argv[1]) != 0) {
		fprintf(stderr, "Parametru invalid\n");
		free(check);
		exit(1);
	}
	free(check);
	hash_table = initHashTable(hash_size);
	hash_table = read(hash_table, argv, argc - 2);
	hash_table = eraseContent(hash_table);
	return 0;
}

