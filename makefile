CC=gcc

MYSQL_PLUGIN_DIR ?= $(shell mysql_config --plugindir 2>/dev/null || mariadb_config --plugindir 2>/dev/null || echo /usr/lib/mysql/plugin)
MYSQL_INCLUDE ?= $(shell pkg-config --cflags mysqlclient 2>/dev/null || pkg-config --cflags mariadb 2>/dev/null)
MYSQL_LIBS ?= $(shell pkg-config --libs mysqlclient 2>/dev/null || pkg-config --libs mariadb 2>/dev/null)
CFLAGS = -I./include $(MYSQL_INCLUDE) -Wall -Wno-char-subscripts


SRC=./src/
BUILD=./build/
COMPILE=@$(CC) $(CFLAGS)

TESTS=$(BUILD)tests
MAIN=$(BUILD)main
DEBUG=$(BUILD)debug
MYSQL_LIB=$(BUILD)liblupa_mysql.so

MYSQL_CMD ?= $(shell which sudo mysql 2>/dev/null || echo "mysql -u root -p")



all: main unitytests debug liblupa_mysql.so
	@echo "Make completed successfully!"

unitytests: $(SRC)tests.c $(BUILD)lupa.o $(BUILD)utf8_utils.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(TESTS) -lm 
	@echo "[ OK ] $@"

main: $(SRC)main.c $(BUILD)lupa.o $(BUILD)utf8_utils.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(MAIN) -lm
	@echo "[ OK ] $@"

debug: $(SRC)debug.c $(BUILD)lupa.o $(BUILD)utf8_utils.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) $^ -o $(DEBUG) -lm
	@echo "[ OK ] $@"


liblupa_mysql.so: $(SRC)lupa_in_mysql.c $(BUILD)lupa.o $(BUILD)utf8_utils.o $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) -fPIC -shared $^ -o $(BUILD)liblupa_mysql.so
	@echo "[ OK ] $@"







$(BUILD)utf8_utils.o: $(SRC)utf8_utils.c 
	$(COMPILE) -fPIC -c $^ -o $@
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

dir:
	@echo "PLUGIN_DIR = $(MYSQL_PLUGIN_DIR)"


install: 
	@sudo cp $(MYSQL_LIB) $(MYSQL_PLUGIN_DIR)
	@echo "[ OK ] Installed at $(MYSQL_PLUGIN_DIR)"

register:
	$(MYSQL_CMD) < register.sql

unregister:
	$(MYSQL_CMD) < unregister.sql

check:
	@QUERY="SELECT * FROM mysql.func WHERE name LIKE 'lupa%';"; \
	echo "$$QUERY"; \
	$(MYSQL_CMD) -e "$$QUERY"

test-sql:
	$(MYSQL_CMD) < teste.sql



.PHONY: build clean run debug dir install




# https://bytes.usc.edu/cs104/wiki/makefile/#cheat-sheet
