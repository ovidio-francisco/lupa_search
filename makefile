CC=gcc
CFLAGS=-I./include
SRC=./src/
BUILD=./build/
COMPILE=$(CC) $(CFLAGS)


TESTS=$(BUILD)tests
MAIN=$(BUILD)main
MYSQL_LIB=$(BUILD)liblupa_mysql.so


all: main unitytests liblupa_mysql.so

unitytests: $(SRC)tests.c $(BUILD)lupa.o  $(BUILD)utils.o
	$(COMPILE) $^ -o $(TESTS)

main: $(SRC)main.c $(BUILD)lupa.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(MAIN)

liblupa_mysql.so: $(SRC)lupa_in_mysql.c $(BUILD)lupa.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	# gcc -fPIC -shared -I./include -I/usr/include/mysql -o $(BUILD)liblupa_mysql.so $(SRC)lupa_in_mysql.c $(BUILD)lupa.o $(BUILD)utils.o
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

.PHONY: build clean check run




# https://bytes.usc.edu/cs104/wiki/makefile/#cheat-sheet
