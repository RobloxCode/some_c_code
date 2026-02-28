CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -fsanitize=address
SRC = day4.c
OUT = d4

volatile:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
