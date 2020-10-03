CC = gcc
SRC = $(wildcard src/*.c) $(wildcard src/*/*.c)
OBJ = $(SRC:.c=.o)
BIN = pac

%.o: %.c
	$(CC) -g -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) -lncurses

.PHONY: clean
clean: $(BIN)
	@rm $(OBJ)
	@rm $(BIN)
