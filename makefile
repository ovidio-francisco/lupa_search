CC=gcc
CFLAGS=-I./include
SRC=./src/
BUILD=./build/
COMPILE=$(CC) $(CFLAGS)


TESTS=$(BUILD)tests
MAIN=$(BUILD)main
DEBUG=$(BUILD)debug
MYSQL_LIB=$(BUILD)liblupa_mysql.so


all: main unitytests debug liblupa_mysql.so

unitytests: $(SRC)tests.c $(BUILD)lupa.o  $(BUILD)utils.o
	$(COMPILE) $^ -o $(TESTS)

main: $(SRC)main.c $(BUILD)lupa.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(MAIN)

debug: $(SRC)debug.c $(BUILD)lupa.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(DEBUG)


liblupa_mysql.so: $(SRC)lupa_in_mysql.c $(BUILD)lupa.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) -fPIC -shared -I/usr/include/mysql $^ -o $(BUILD)liblupa_mysql.so

$(BUILD)utils.o: $(SRC)utils.c
	$(COMPILE) -c $^ -o $(BUILD)utils.o

$(BUILD)phoneticBr.o: $(SRC)phoneticBr.c
	$(COMPILE) -fPIC -c $^ -o $(BUILD)phoneticBr.o

$(BUILD)lupa.o: $(SRC)lupa.c build 
	$(COMPILE) -c $(SRC)lupa.c -o $(BUILD)lupa.o



build:
	mkdir -p $(BUILD)

clean:
	rm -rvf $(TESTS) $(MAIN) $(BUILD)*.o $(BUILD)

tests:
	$(TESTS)

run:
	$(MAIN)

deb: debug
	$(DEBUG)

.PHONY: build clean run debug




# https://bytes.usc.edu/cs104/wiki/makefile/#cheat-sheet
