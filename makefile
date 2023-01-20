CC=gcc
CFLAGS=-I./include
SRC=./src/
BIN=./bin/
INCLUDE=./include/



lupa: main.o lupa.o
	$(CC) main.o lupa.o -o $(BIN)lupa

main.o: $(SRC)/main.c include/lupa.h
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o main.o

lupa.o: $(SRC)/lupa.c include/lupa.h
	$(CC) $(CFLAGS) -c src/lupa.c -o lupa.o

clean:
	rm -rvf lupa *.o


