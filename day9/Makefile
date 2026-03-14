CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -fsanitize=address
# UTILS = ../utils/Stack/StackImp.c
SRC = day9.c
OUT = d9

volatile:
	$(CC) $(UTILS) $(SRC) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
