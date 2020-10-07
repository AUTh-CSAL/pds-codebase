# ####################################################################
#
#			   C/C++ Makefile
#
# Author: Dimitris Floros <fcdimitr@auth.gr>
#
# ####################################################################

# define the C/C++ compiler to use
CC = gcc-7

# define compile-time flags
CFLAGS = -O3 -fcilkplus -Wall

# executable file name
MAIN = fib

all: $(MAIN) run plot

plot:
	julia -e 'include("parse.jl")'

run:
	./fib > run.log

$(MAIN): $(MAIN).o
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LIBS)


# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	$(RM) *.o *~ fib *.log
