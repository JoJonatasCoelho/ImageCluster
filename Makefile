all: cluster

cluster: main.o src/cluster.o src/pgm.o
	gcc -O3 -Iinclude main.o src/cluster.o src/pgm.o -o cluster

main.o: main.c
	gcc -O3 -Iinclude -c main.c -o main.o

src/cluster.o: src/cluster.c
	gcc -O3 -Iinclude -c src/cluster.c -o src/cluster.o

src/pgm.o: src/pgm.c
	gcc -O3 -Iinclude -c src/pgm.c -o src/pgm.o

clean:
	rm -f main.o src/cluster.o src/pgm.o cluster

