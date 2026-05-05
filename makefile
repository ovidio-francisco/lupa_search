CC=gcc
CFLAGS=-I./include -Wall -Wno-char-subscripts
CFLAGS = -I./include -I/usr/include/mysql -I/usr/include/mariadb -Wall -Wno-char-subscripts
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
	@echo "[ OK ] $@"

main: $(SRC)main.c $(BUILD)lupa.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(MAIN) -lm
	@echo "[ OK ] $@"

debug: $(SRC)debug.c $(BUILD)lupa.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(DEBUG) -lm
	@echo "[ OK ] $@"


liblupa_mysql.so: $(SRC)lupa_in_mysql.c $(BUILD)lupa.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) -fPIC -shared $^ -o $(BUILD)liblupa_mysql.so
	@echo "[ OK ] $@"







$(BUILD)utils.o: $(SRC)utils.c 
	$(COMPILE) -fPIC -c $^ -o $@
	@echo "[ OK ] $@"

$(BUILD)buffers.o: $(SRC)buffers.c
	$(COMPILE) -fPIC -c $^ -o $@
	@echo "[ OK ] $@"


$(BUILD)phoneticBr.o: $(SRC)phoneticBr.c
	$(COMPILE) -fPIC -c $^ -o $(BUILD)phoneticBr.o
	@echo "[ OK ] $@"

$(BUILD)lupa.o: $(SRC)lupa.c build 
	$(COMPILE) -c $(SRC)lupa.c -o $(BUILD)lupa.o
	@echo "[ OK ] $@"

build:
	@mkdir -p $(BUILD)

clean:
	rm -rvf $(TESTS) $(MAIN) $(BUILD)*.o $(BUILD)

tests: unitytests
	@echo "Running $(TESTS)"
	@$(TESTS)

run:
	$(MAIN)

deb: debug
	$(DEBUG)

.PHONY: build clean run debug




# https://bytes.usc.edu/cs104/wiki/makefile/#cheat-sheet
