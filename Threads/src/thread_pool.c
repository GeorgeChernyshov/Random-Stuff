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
            if(task->f) task->f(task->arg);
            pthread_mutex_lock(&task->mutex);
            pthread_cond_signal(&task->cond);
            pthread_mutex_unlock(&task->mutex);
            destroy_task(task);
        }
    }
    return NULL;
}

struct Task* create_task(void){
    struct Task* task = malloc(sizeof(struct Task));
    pthread_mutex_init(&task->mutex, NULL);
    pthread_cond_init(&task->cond, NULL);
    return task;
}

void destroy_task(struct Task* task){
    free(task->arg);
    pthread_mutex_destroy(&task->mutex);
    pthread_cond_destroy(&task->cond);
    free(task);    
}

void thpool_init(struct ThreadPool* pool, unsigned threads_nm){
    pthread_mutex_init(&pool->pool_mutex, NULL);
    pool->threads = malloc(threads_nm * sizeof(pthread_t));
    pool->tasks = malloc(sizeof(struct wsqueue));
    wsqueue_init(pool->tasks);
    pool->num = threads_nm;
    for (unsigned i = 0; i < threads_nm; i++){
        pthread_create(&pool->threads[i], NULL, thpool_go, pool);
    }
}

void thpool_finit(struct ThreadPool* pool){
    pthread_mutex_destroy(&pool->pool_mutex);
    free(pool->threads);
    wsqueue_finit(pool->tasks);
    free(pool->tasks);
}

void thpool_submit(struct ThreadPool* pool, struct Task* task){
    pthread_mutex_lock(&pool->pool_mutex);
    wsqueue_push(pool->tasks, (struct list_node*) task);
    pthread_mutex_unlock(&pool->pool_mutex);
}

void thpool_wait(struct Task* task){
    pthread_mutex_lock(&task->mutex);
    while(!task->complete){
        pthread_cond_wait(&task->cond, &task->mutex);
    }
    pthread_mutex_unlock(&task->mutex);
}
