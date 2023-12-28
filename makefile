CC=gcc
CFLAGS=-I./include -Wall -Wno-char-subscripts
SRC=./src/
BUILD=./build/
COMPILE=@$(CC) $(CFLAGS)

TESTS=$(BUILD)tests
MAIN=$(BUILD)main
DEBUG=$(BUILD)debug
MYSQL_LIB=$(BUILD)liblupa_mysql.so


all: main unitytests debug liblupa_mysql.so
	@echo "Make completed successfully!"

unitytests: $(SRC)tests.c $(BUILD)lupa.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(TESTS) -lm 

main: $(SRC)main.c $(BUILD)lupa.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(MAIN) -lm

debug: $(SRC)debug.c $(BUILD)lupa.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(DEBUG) -lm


liblupa_mysql.so: $(SRC)lupa_in_mysql.c $(BUILD)lupa.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) -fPIC -shared -I/usr/include/mysql $^ -o $(BUILD)liblupa_mysql.so


$(BUILD)utils.o: $(SRC)utils.c 
	$(COMPILE) -fPIC -c $^ -o $@

$(BUILD)buffers.o: $(SRC)buffers.c
	$(COMPILE) -fPIC -c $^ -o $@


$(BUILD)phoneticBr.o: $(SRC)phoneticBr.c
	$(COMPILE) -fPIC -c $^ -o $(BUILD)phoneticBr.o

$(BUILD)lupa.o: $(SRC)lupa.c build 
	$(COMPILE) -c $(SRC)lupa.c -o $(BUILD)lupa.o

build:
	@mkdir -p $(BUILD)

clean:
	rm -rvf $(TESTS) $(MAIN) $(BUILD)*.o $(BUILD)

tests: unitytests
	$(TESTS)

run:
	$(MAIN)

deb: debug
	$(DEBUG)

.PHONY: build clean run debug




# https://bytes.usc.edu/cs104/wiki/makefile/#cheat-sheet
