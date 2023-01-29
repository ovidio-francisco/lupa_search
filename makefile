CC=gcc
CFLAGS=-I./include
SRC=./src/
BIN=./bin/
INCLUDE=./include/


tests: tests.o lupa.o
	$(CC) tests.o lupa.o -o $(BIN)tests

tests.o: $(SRC)/tests.c
	$(CC) $(CFLAGS) -c $(SRC)/tests.c -o tests.o


lupa: main.o lupa.o
	$(CC) main.o lupa.o -o $(BIN)lupa

main.o: $(SRC)/main.c 
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o main.o

lupa.o: $(SRC)/lupa.c 
	$(CC) $(CFLAGS) -c src/lupa.c -o lupa.o

clean:
	rm -rvf lupa tests *.o


