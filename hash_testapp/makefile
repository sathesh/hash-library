INCLUDES = ../src/

all: test_hash

test_hash: test_hash.o hash.o
	gcc -o test_hash test_hash.o hash.o

test_hash.o: test_hash.c  ../src/hash.h
	gcc -c test_hash.c -I $(INCLUDES) -o test_hash.o -g

hash.o: ../src/hash.c ../src/hash.h
	gcc -c $(INCLUDES) ../src/hash.c -o hash.o -g

clean:
	rm hash.o test_hash test_hash.o
