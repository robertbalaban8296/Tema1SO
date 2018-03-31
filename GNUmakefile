CC=gcc
CFLAGS=-Wall -fPIC

build: main.o hash_table.o list.o
	$(CC) $(CFLAGS) -g -Ihash -Ihash_table -Ilist main.o hash_table.o list.o -o tema1 -lhash -L. 

main.o: main.c
	$(CC) $(CFLAGS) -c $< -Ihash -Ihash_table -Ilist
hash_table.o: hash_table.c
	$(CC) $(CFLAGS) -c $< -Ihash -Ihash_table -Ilist
list.o: list.c
	$(CC) $(CFLAGS) -c $< -Ilist
clean:
	rm -f main.o
