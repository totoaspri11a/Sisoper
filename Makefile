all: punto1 punto2

clean:
	rm -f punto1 punto2

punto1:
	gcc -o punto1 partitioning.c -Wall

punto2:
	gcc -o punto2 allocation.c -Wall
