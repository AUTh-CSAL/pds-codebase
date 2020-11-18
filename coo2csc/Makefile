CC=gcc

default: all

hello_coo2csc:
	$(CC) $(CFLAGS) -o hello_coo2csc coo2csc.c 

.PHONY: clean

all: 	hello_coo2csc

test:
	@printf "\n** Testing coo2csc\n\n"
	./hello_coo2csc
clean:
	rm -f hello_coo2csc
