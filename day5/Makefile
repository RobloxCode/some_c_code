CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -fsanitize=address
UTILS = ../utils/ArrayList/ArrayListImp.c
SRC = day5.c
OUT = d5

volatile:
	$(CC) $(UTILS) $(SRC) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
