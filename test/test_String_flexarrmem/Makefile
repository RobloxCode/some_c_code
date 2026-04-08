CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -g \
         -fsanitize=address -fno-omit-frame-pointer

SRC = test.c ../../utils/String_using_flexarrmem/String.c
OUT = test

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OUT)

.PHONY: clean
