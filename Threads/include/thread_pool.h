#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "wsqueue.h"

struct Task {
    struct list_node link;
	void (*f)(void *);
	void* arg;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
	int complete;
	int free_arg;
	int free;
};

struct ThreadPool {
    pthread_t* threads;
    struct wsqueue* tasks;
    struct wsqueue* tasks_to_delete;
    unsigned num;
    int is_working;
    pthread_mutex_t pool_mutex;
};

void thpool_init(struct ThreadPool* pool, unsigned threads_nm);
void thpool_submit(struct ThreadPool* pool, struct Task* task);
void thpool_wait(struct Task* task);
void thpool_finit(struct ThreadPool* pool);
struct Task* create_task(void);
void destroy_task(struct Task* task);

