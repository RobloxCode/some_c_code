CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -fsanitize=address
# UTILS = ../utils/String/StringImp.c
SRC = day7.c
OUT = d7

volatile:
	$(CC) $(UTILS) $(SRC) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
