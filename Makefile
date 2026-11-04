CC = gcc
CFLAGS = -Wall -Wextra -g -Icli-lib/include -Iinclude
ifdef DEBUG
CFLAGS += -DDEBUG
endif
LIB_SRC = $(filter-out cli-lib/src/main.c, $(wildcard cli-lib/src/*.c))
SRC = $(wildcard src/*.c) $(LIB_SRC)
TARGET = guitar-hero

all: $(TARGET)

$(TARGET): $(SRC) include/config.h
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
