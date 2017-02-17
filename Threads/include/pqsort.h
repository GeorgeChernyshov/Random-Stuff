#pragma once
#include <pthread.h>
#include "thread_pool.h"

void sort_array(int depth, int max_depth, int* x, int N, struct ThreadPool* pool);
int comp (const int *i, const int *j);
struct Task* create_task(void);
void destroy_task(struct Task* task);

