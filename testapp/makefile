INCLUDES = ../hashlib/

FLAGS = -DDEBUG \
        -g \
        -Werror

all: testapp

testapp: testapp.o hash.o
	gcc $(FLAGS) -o testapp testapp.o hash.o

testapp.o: testapp.c  ../hashlib/hash.h
	gcc $(FLAGS) -I $(INCLUDES) -c testapp.c  -o testapp.o 

hash.o: ../hashlib/hash.c ../hashlib/hash.h
	gcc $(FLAGS) -I  $(INCLUDES) -c ../hashlib/hash.c -o hash.o 

clean:
	rm hash.o testapp testapp.o







