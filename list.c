#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

List initList(int key, const char *value)
{
	List l = (List)malloc(sizeof(struct list));

	l->key = key;
	l->value = (char *)malloc(sizeof(char) * (strlen(value) + 1));
	strcpy(l->value, value);
	l->next = NULL;
	return l;
}

int containsValue(List l, const char *cuvant)
{
	List aux = l;

	while (aux != NULL) {
		if (strcmp(aux->value, cuvant) == 0)
			return 1;
		aux = aux->next;
	}
	return 0;
}

List removeFromBucket(List l, const char *value)
{
	List aux = l;
	List prev = NULL;

	while (aux != NULL) {
		if (strcmp(aux->value, value) == 0) {
			if (prev == NULL) {
				prev = aux->next;
				aux->next = NULL;
				free(aux->value);
				free(aux);
				return prev;
			}
			prev->next = aux->next;
			free(aux->value);
			free(aux);
			return l;
		}
		prev = aux;
		aux = aux->next;
	}
	return l;
}

List addLast(List l, int key, const char *value)
{
	List newItem = initList(key, value);
	List aux;

	if (l == NULL)
		return newItem;
	aux = l;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = newItem;
	return l;
}

List freeBucket(List l)
{
	List aux = NULL;

	while (l != NULL) {
		aux = l;
		l = l->next;
		free(aux->value);
		free(aux);
	}
	return NULL;
}
