#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "hash_table.h"
#include <stdlib.h>
#include "hash.h"

HashTable initHashTable(unsigned int hash_size)
{
	unsigned int i;
	HashTable hash_table = (HashTable)malloc(sizeof(struct hash_table));

	hash_table->size = hash_size;
	hash_table->buckets = (List *)malloc(sizeof(List) * hash_size);
	for (i = 0 ; i < hash_size; i++)
		hash_table->buckets[i] = NULL;
	return hash_table;
}

HashTable clear(HashTable h)
{
	int i;

	for (i = 0; i < h->size; i++)
		h->buckets[i] = freeBucket(h->buckets[i]);
	return h;
}

HashTable eraseContent(HashTable hash_table)
{
	hash_table = clear(hash_table);
	free(hash_table->buckets);
	free(hash_table);
	return NULL;
}

HashTable add(HashTable hash_table, const char *c)
{
	if (c != NULL && strcmp(c, "") != 0) {
		unsigned int i = hash(c, hash_table->size);
		List b = hash_table->buckets[i];

		if (containsValue(hash_table->buckets[i], c) == 0)
			hash_table->buckets[i] = addLast(b, i, c);
	}
	return hash_table;
}

HashTable resize(HashTable old_table, const char *mode)
{
	HashTable new_table = NULL;
	int i;
	unsigned int size = old_table->size;

	if (strcmp(mode, "double") == 0)
		size *= 2;
	if (strcmp(mode, "halve") == 0)
		size /= 2;
	new_table = initHashTable(size);
	for (i = 0; i < old_table->size; i++) {
		List bucket = old_table->buckets[i];
		List a = NULL;

		while (bucket != NULL) {
			new_table = add(new_table, bucket->value);
			a = bucket;
			free(bucket->value);
			bucket = bucket->next;
			free(a);
		}
		free(bucket);
	}
	free(old_table->buckets);
	free(old_table);
	return new_table;
}

HashTable removeWord(HashTable hash_table, const char *c)
{
	unsigned int i = hash(c, hash_table->size);

	hash_table->buckets[i] = removeFromBucket(hash_table->buckets[i], c);
	return hash_table;
}

void print_bucket(HashTable hash_table, int index, const char *fileName)
{
	if (index >= 0 && index < hash_table->size) {
		FILE *fp = NULL;
		List bucket = hash_table->buckets[index];

		if (strcmp(fileName, "") != 0)
			fp = fopen(fileName, "a");
		while (bucket != NULL) {
			if (fp == NULL) {
				if (bucket->next == NULL)
					fprintf(stdout, "%s\n", bucket->value);
				else
					fprintf(stdout, "%s ", bucket->value);
			} else {
				if (bucket->next == NULL)
					fprintf(fp, "%s\n", bucket->value);
				else
					fprintf(fp, "%s ", bucket->value);
			}
			bucket = bucket->next;
		}
		if (fp != NULL)
			fclose(fp);
	}
}

void print(HashTable hash_table, const char *fileName)
{
	unsigned int i;

	for (i = 0; i < hash_table->size; i++)
		print_bucket(hash_table, i, fileName);
}

void findEl(HashTable hash_table, const char *cuvant, const char *fileName)
{
	int index = hash(cuvant, hash_table->size);
	int rezultat = 0;
	FILE *fp = NULL;
	List aux = hash_table->buckets[index];

	if (containsValue(aux, cuvant) != 0)
		rezultat = 1;
	if (fileName != NULL && strcmp(fileName, "") != 0)
		fp = fopen(fileName, "a");
	if (fp == NULL) {
		if (rezultat == 1)
			printf("%s\n", "True");
		else
			printf("%s\n", "False");
	} else {
		if (rezultat == 1)
			fprintf(fp, "%s\n", "True");
		else
			fprintf(fp, "%s\n", "False");
	}
	if (fp != NULL)
		fclose(fp);
}

HashTable callFunction(HashTable hash_table, char *cmd)
{
	char token[20000];
	char *buf;
	int validCmd = 0;

	strcpy(token, cmd);
	buf = strtok(token, "\n\r ");
	if (buf == NULL)
		return hash_table;
	if (strcmp(buf, "add") == 0) {
		buf  = strtok(NULL, "\n\r ");
		if (buf == NULL) {
			fprintf(stderr, "\nArgument 2 invalid\n");
			exit(1);
		}
		hash_table = add(hash_table, buf);
		validCmd = 1;
	}
	if (strcmp(buf, "remove") == 0) {
		buf  = strtok(NULL, "\n\r ");
		hash_table = removeWord(hash_table, buf);
		validCmd = 1;
	}
	if (strcmp(buf, "find") == 0) {
		char *el;

		buf = strtok(NULL, "\n\r ");
		el = buf;
		buf = strtok(NULL, "\n\r ");
		if (buf == NULL)
			buf = "";
		findEl(hash_table, el, buf);
		validCmd = 1;
	}
	if (strcmp(buf, "clear") == 0) {
		hash_table = clear(hash_table);
		validCmd = 1;
	}
	if (strcmp(buf, "resize") == 0) {
		buf = strtok(NULL, "\n\r ");
		hash_table = resize(hash_table, buf);
		validCmd = 1;
	}
	if (strcmp(buf, "print_bucket") == 0) {
		char *check;
		int index;

		buf = strtok(NULL, "\n\r ");
		check = (char *)malloc(sizeof(char) * (strlen(buf) + 1));
		index = atoi(buf);
		sprintf(check, "%d", index);
		if (strcmp(check, buf) != 0) {
			fprintf(stderr, "\nParametru invalid\n");
			free(check);
			free(cmd);
			exit(1);
		}
		free(check);
		buf = strtok(NULL, "\n\r ");
		if (buf == NULL)
			buf = "";
		print_bucket(hash_table, index, buf);
		validCmd = 1;
	}
	if (strcmp(buf, "print") == 0) {
		buf = strtok(NULL, "\n ");
		if (buf == NULL)
			buf = "";
		print(hash_table, buf);
		validCmd = 1;
	}
	if (validCmd == 0) {
		fprintf(stderr, "\nComanda invalida\n");
		free(cmd);
		exit(1);
	}
	return hash_table;
}

HashTable read(HashTable h, char *argv[], int numOfFiles)
{
	FILE *fp;
	char *readBuff = (char *)malloc(sizeof(char) * 20000);
	int i;

	if (numOfFiles <= 0) {
		while ((fgets(readBuff, 20000, stdin)) != NULL)
			h = callFunction(h, readBuff);
	} else {
		for (i = 0; i < numOfFiles; i++) {
			fp = fopen(argv[i + 2], "r");
			if (fp == NULL)
				continue;
			while ((fgets(readBuff, 20000, (FILE *)fp)) != NULL)
				h = callFunction(h, readBuff);
			if (fp != NULL)
				fclose(fp);
		}
	}
	free(readBuff);
	return h;
}


