#ifndef PQSORT_H_INCLUDED
#define PQSORT_H_INCLUDED
#include "thread_pool.h"

void sort_array(int depth, int max_depth, int* x, int N, struct ThreadPool* pool, int threads_num);
int comp (const int *i, const int *j);

#endif // PQSORT_H_INCLUDED
