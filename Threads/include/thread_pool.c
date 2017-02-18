#include <stdio.h>
#include <stdlib.h>
#include "thread_pool.h"
#include <pthread.h>

void* thpool_go(void* arg){
    struct ThreadPool* pool = arg;
    while(1){
        wsqueue_wait(pool->tasks);
        struct list_node* node = wsqueue_pop(pool->tasks);
        if(node){
            struct Task* task = (struct Task*) node;
            task->f(task->arg);
            pthread_mutex_lock(&task->mutex);
            task->complete = 1;
            pthread_cond_broadcast(&task->cond);
            pthread_mutex_unlock(&task->mutex);            
        }
    }
    return NULL;
}

void thpool_init(struct ThreadPool* pool, unsigned threads_nm){
    pool->threads = malloc(threads_nm * sizeof(pthread_t));
    pool->num = threads_nm;
    wsqueue_init(pool->tasks);
    for (unsigned i = 0; i < threads_nm; i++){
        pthread_create(&pool->threads[i], NULL, thpool_go, pool);
    }
}

void thpool_finit(struct ThreadPool* pool){
    struct Task task;
    task.arg = NULL;
    task.f = pthread_exit;
    task.complete = 0;
    for (unsigned i = 0; i < pool->num; i++){
        wsqueue_push(pool->tasks, (struct list_node*) (&task));
    }
    for (unsigned i = 0; i < pool->num; i++){
        pthread_join(pool->threads[i], NULL);
    }
    free(pool->threads);
    wsqueue_finit(pool->tasks);
}

void thpool_submit(struct ThreadPool* pool, struct Task* task){
    wsqueue_push(pool->tasks, (struct list_node*) task);
}

void thpool_wait(struct Task* task){
    pthread_mutex_lock(&task->mutex);
    while(!(task->complete)){
        pthread_cond_wait(&task->cond, &task->mutex);
    }
    pthread_mutex_unlock(&task->mutex);
}
