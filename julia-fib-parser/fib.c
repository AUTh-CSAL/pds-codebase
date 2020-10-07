/*
 * fib.c
 *
 * Implementation of Fibonacci using cilk_spawn
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

#define NITER 4

struct timeval tic(){
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv;
}

double toc(struct timeval begin){
  struct timeval end;
  gettimeofday(&end, NULL);
  double stime = ((double) (end.tv_sec - begin.tv_sec) * 1000 ) +
    ((double) (end.tv_usec - begin.tv_usec) / 1000 );
  stime = stime / 1000;
  return(stime);
}


void setWorkers(int n){
    char buf[10];
    sprintf(buf, "%d", n);

    __cilkrts_end_cilk();
    if ( 0!=__cilkrts_set_param("nworkers", buf ) )
      printf( "Error setting workers\n" );
}

int fib(int n) {
  if (n < 2)
    return n;
  int x = cilk_spawn fib(n-1);
  int y = fib(n-2);
  cilk_sync;
  return x + y;
}

int main(){

  int Nmin = 21, Nmax = 35;
  int P = 4;

  printf("np,n,fib,time\n");

  for (int i = 0; i<P; i++){
    int np = 1 << i;
    setWorkers( np );
    for (int j = Nmin; j<=Nmax; j++){
      printf("%d,%d,%d", np, j, fib(j));
      for (int iter = 0; iter < NITER; iter++){
        struct timeval tStart = tic();
        fib(j);
        printf(",%.6f", toc(tStart));
      }
      printf("\n");
    }
  }

  return 0;
}
