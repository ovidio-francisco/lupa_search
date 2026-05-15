#                  _         __ _ _
#  _ __ ___   __ _| | _____ / _(_) | ___
# | '_ ` _ \ / _` | |/ / _ \ |_| | |/ _ \
# | | | | | | (_| |   <  __/  _| | |  __/
# |_| |_| |_|\__,_|_|\_\___|_| |_|_|\___|



CC=gcc

MYSQL_PLUGIN_DIR ?= $(shell mysqld --verbose --help 2>/dev/null | grep "^plugin-dir" | awk '{print $$2}' \
					     || mariadbd --verbose --help 2>/dev/null | grep "^plugin-dir" | awk '{print $$2}' \
                         || echo /usr/lib/mysql/plugin)

MYSQL_INCLUDE ?= $(shell pkg-config --cflags mysqlclient 2>/dev/null || pkg-config --cflags mariadb 2>/dev/null)
MYSQL_LIBS ?= $(shell pkg-config --libs mysqlclient 2>/dev/null || pkg-config --libs mariadb 2>/dev/null)
CFLAGS = -I./include $(MYSQL_INCLUDE) -I/usr/include/mariadb/server -Wall -Wno-char-subscripts -Wno-cpp


SRC=./src/
BUILD=./build/
COMPILE=@$(CC) $(CFLAGS)

TESTS=$(BUILD)tests
MAIN=$(BUILD)main
DEBUG=$(BUILD)debug
MYSQL_LIB=$(BUILD)liblupa_mysql.so
MYSQL_PLUGIN_LIB=$(BUILD)lupa.so

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


plugin: $(SRC)plugin.c $(SRC)lupa_in_mysql.c $(BUILD)lupa.o  $(BUILD)utf8_utils.o   $(BUILD)buffers.o $(BUILD)utils.o $(BUILD)phoneticBr.o
	$(COMPILE) -fPIC -shared -DMYSQL_DYNAMIC_PLUGIN $^ -o $(MYSQL_PLUGIN_LIB)
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
	@sudo cp $(MYSQL_PLUGIN_LIB) $(MYSQL_PLUGIN_DIR)
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



.PHONY: build clean run debug dir install plugin




# https://bytes.usc.edu/cs104/wiki/makefile/#cheat-sheet
