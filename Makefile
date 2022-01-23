CC=gcc --std=c99 -g

all: dijkstra

dijkstra: dijkstra.c pq.o dynarray.o
	$(CC) dijkstra.c pq.o dynarray.o -o dijkstra

dynarray.o: dynarray.c dynarray.h
	$(CC) -c dynarray.c

pq.o: pq.c pq.h
	$(CC) -c pq.c

clean:
	rm -f *.o dijkstra
	rm -rf *.dSYM/