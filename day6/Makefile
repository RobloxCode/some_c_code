CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -fsanitize=address
UTILS = ../utils/ArrayList/ArrayListImp.c
SRC = day6.c
OUT = d6

volatile:
	$(CC) $(UTILS) $(SRC) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
