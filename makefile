all: graph

.PHONY: clean

clean:
	rm -f *.o *.a *.so graph

graph: main.o
	gcc -Wall -g -o graph main.o algo.o Edge.o graph.o

main.o: main.c algo.o Edge.o graph.o declarations.h
	gcc -Wall -g -c main.c 

algo.o: algo.c declarations.h
	gcc -Wall -g -c algo.c

Edge.o: Edge.c declarations.h
	gcc -Wall -g -c Edge.c

graph.o: graph.c declarations.h
	gcc -Wall -g -c graph.c