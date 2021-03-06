#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "pqsort.h"

int main(int argc, char **argv){
    if(argc == 4){
        int threads_num = atoi(argv[1]);
        int N = atoi(argv[2]);
        int d = atoi(argv[3]);
        int *x = malloc(sizeof(int)*N);
        int *y = malloc(sizeof(int)*N);
        for (int i = 0; i < N; i++){
            x[i] = rand();
            y[i] = x[i];
        }
        qsort(y, N, sizeof (int), (int(*) (const void *, const void *)) comp);
        struct ThreadPool pool;
        thpool_init(&pool, threads_num);
        sort_array(0, d, x, N, &pool);
        thpool_finit(&pool);
        for (int i = 0; i < N; i++){
            assert(x[i] == y[i]);
        }
        free(x);
        free(y);
    }else{
        printf("Wrong parameters");
    }
    return 0;
}
