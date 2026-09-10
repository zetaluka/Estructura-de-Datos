CC=gcc
EXEC=build/tarea2.out
CFLAGS = -Wall -Wextra -Iinc

SRC = src/main.c src/funciones.c
OBJ = build/main.o build/funciones.o
DEPS = inc/commons.h

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

build/%.o: src/%.c $(DEPS) | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

.PHONY: all clean run

all: $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f build/*.o $(EXEC)