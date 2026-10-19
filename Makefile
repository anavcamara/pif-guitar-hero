CC = gcc
CFLAGS = -Wall -Wextra -g -Icli-lib/include -Iinclude
LIB_SRC = $(filter-out cli-lib/src/main.c, $(wildcard cli-lib/src/*.c))
SRC = $(wildcard src/*.c) $(LIB_SRC)
TARGET = guitar-hero

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)