CC=gcc
CFLAGS = -O3

default: all

readmtx: readmtx.c
	$(CC) $(CFLAGS) -o $@ $^ mmio.c

.PHONY: clean

all: 	readmtx

test: readmtx
	@printf "\n** Testing coo2csc\n\n"
	./readmtx s12.mtx
clean:
	rm -f readmtx
