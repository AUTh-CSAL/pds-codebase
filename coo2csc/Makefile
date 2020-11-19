CC=gcc
CFLAGS = -O3

default: all

hello_coo2csc: coo2csc.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

all: 	hello_coo2csc

test: hello_coo2csc
	@printf "\n** Testing coo2csc\n\n"
	./hello_coo2csc
clean:
	rm -f hello_coo2csc
