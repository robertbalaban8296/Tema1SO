
typedef struct list {
	char *value;
	int key;
	struct list *next;
} *List;

List initList(int key, const char *value);

int containsValue(List l, const char *cuvant);

List removeFromBucket(List l, const char *value);

List addLast(List l, int key, const char *value);

List freeBucket(List l);

