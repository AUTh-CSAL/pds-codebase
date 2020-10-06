CC=gcc
MPICC=mpicc
CILKCC=/usr/local/OpenCilk-9.0.1-Linux/bin/clang
CFLAGS=-O3

default: all

hello_openmp: 
	$(CC) $(CFLAGS) -o hello_openmp hello_openmp.c -fopenmp

hello_threads:
	$(CC) $(CFLAGS) -o hello_threads hello_threads.c -lpthread

hello_mpi:
	$(MPICC) $(CFLAGS) -o hello_mpi hello_mpi.c

hello_cilk:
	$(CILKCC) $(CFLAGS) -o hello_cilk hello_cilk.c -fcilkplus

.PHONY: clean

all: hello_openmp hello_mpi hello_threads hello_cilk

test:
	@printf "\n** Testing pthreads\n\n"
	./hello_threads
	@printf "\n** Testing OpenMP\n\n"
	./hello_openmp
	@printf "\n** Testing Cilk\n\n"
	./hello_cilk
	@printf "\n\n** Testing MPI\n\n"
	mpirun ./hello_mpi

clean:
	rm -f hello_openmp hello_mpi hello_cilk hello_threads 
