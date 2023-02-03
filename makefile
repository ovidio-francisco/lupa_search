CC=gcc
CFLAGS=-I./include
SRC=./src/
BUILD=./build/
COMPILE=$(CC) $(CFLAGS)


TESTS=$(BUILD)tests
MAIN=$(BUILD)main


all: main unitytests

unitytests: $(SRC)tests.c $(BUILD)lupa.o
	$(COMPILE) $^ -o $(TESTS)

main: $(SRC)main.c $(BUILD)lupa.o
	$(COMPILE) $^ -o $(MAIN)


$(BUILD)lupa.o: $(SRC)lupa.c  build
	$(COMPILE) -c $(SRC)lupa.c -o $(BUILD)lupa.o

build:
	mkdir -p $(BUILD)

clean:
	rm -rvf $(TESTS) $(MAIN) $(BUILD)*.o $(BUILD)

test:
	$(TESTS)

run:
	$(MAIN)

.PHONY: build clean check run





