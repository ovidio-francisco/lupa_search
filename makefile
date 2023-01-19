CC=gcc
CFLAGS=-I./include

lupa: main.o lupa.o
	$(CC) main.o lupa.o -o lupa

main.o: src/main.c include/lupa.h
	$(CC) $(CFLAGS) -c ./src/main.c -o main.o

lupa.o: src/lupa.c include/lupa.h
	$(CC) $(CFLAGS) -c src/lupa.c -o lupa.o

clean:
	rm -rf lupa *.o


