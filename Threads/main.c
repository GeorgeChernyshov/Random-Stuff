#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqsort.h"


int x[100000];
int y[100000];
int N, d, threads_num;

int main(){
  scanf("%d %d %d", &threads_num, &N, &d);
  for (int i = 0; i < N; i++){
      x[i] = rand();
      y[i] = x[i];
  }
  qsort(y, N, sizeof (int), (int(*) (const void *, const void *)) comp);
  struct ThreadPool pool;
  sort_array(0, d, x, N, &pool, threads_num);
  for (int i = 0; i < N; i++){
      assert(x[i] == y[i]);
  }
  return 0;
}
