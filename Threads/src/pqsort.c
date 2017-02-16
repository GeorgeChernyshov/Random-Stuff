#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pqsort.h"
#include "thread_pool.h"

int done;
struct wsqueue queue;
    
struct Args {
    int depth;
    int max_depth;
    int left;
    int right;
    int* arr;
    struct ThreadPool* pool;
    pthread_mutex_t *done_mutex;
    pthread_cond_t *cond_exit;
    struct Task* task;
};

void pqsort(void* a);

void create_args(struct Task* task, int left, int right, struct Args *ar){
    struct Args* args = malloc(sizeof(struct Args));
    args->depth = ar->depth;
    args->max_depth = ar->max_depth;
    args->left = left;
    args->right = right;
    args->arr = ar->arr;
    args->pool = ar->pool;
    args->done_mutex = ar->done_mutex;
    args->cond_exit = ar->cond_exit;
    task->arg = args;
    args->task = task;
}

int q_partition(int left, int right, int* a){
    int i = left; int j = right - 1;
    int ind = rand() % (right - left) + left;
    int x = a[ind];
    while(i <= j) {
        while(a[i] < x) i++;
        while(a[j] > x) j--;
        if (i <= j) {
            int tmp = a[i];
            a[i++] = a[j];
            a[j--] = tmp;
        }
    }
    return i;
}

void submit_qsort_task(int left, int right, struct Args* args){
    if(args->depth >= args->max_depth){
        qsort(args->arr+left, (right-left), sizeof (int), (int(*) (const void *, const void *)) comp);
        pthread_mutex_lock(args->done_mutex);
        done -= (right-left);
        if(done == 0) pthread_cond_signal(args->cond_exit);
        pthread_mutex_unlock(args->done_mutex);
    }else{
        if(right - left == 1) {
            pthread_mutex_lock(args->done_mutex);
            done--;
            if(done == 0) pthread_cond_signal(args->cond_exit);  
            pthread_mutex_unlock(args->done_mutex);
        }
        if(right - left > 1) {
            struct Task* task = create_task();
            task->f = pqsort;
            create_args(task, left, right, args);
            thpool_submit(args->pool, task);
        }   
    }
}

int comp (const int *i, const int *j){
     return *i - *j;
}

void pqsort(void* a){
    struct Args* args = a;
    int new_border = q_partition(args->left, args->right, args->arr);
    args->depth++;
    submit_qsort_task(args->left, new_border, args);
    submit_qsort_task(new_border, args->right, args);
}

struct Task* create_task(void){
    struct Task* task = malloc(sizeof(struct Task));
    task->complete = 0;
    pthread_mutex_init(&task->mutex, NULL);
    pthread_cond_init(&task->cond, NULL);
    wsqueue_push(&queue, (struct list_node*) (task));
    return task;
}

void destroy_task(struct Task* task){
    free(task->arg);
    pthread_mutex_destroy(&task->mutex);
    pthread_cond_destroy(&task->cond);
    free(task);    
}

void sort_array(int depth, int max_depth, int* x, int N, struct ThreadPool* pool, int threads_num){
    done = N;
    thpool_init(pool, threads_num);
    pthread_mutex_t done_mutex;
    pthread_cond_t cond_exit;
    pthread_mutex_init(&done_mutex, NULL);
    pthread_cond_init(&cond_exit, NULL);
    struct Args* args = malloc(sizeof(struct Args));
    wsqueue_init(&queue);
    args->depth = depth;
    args->max_depth = max_depth;
    args->left = 0;
    args->right = N;
    args->arr = x;
    args->pool = pool;
    args->done_mutex = &done_mutex;
    args->cond_exit = &cond_exit;
    submit_qsort_task(0, N, args);
    pthread_cond_wait(&cond_exit, &done_mutex);
    thpool_finit(pool);
    free(args);
    pthread_mutex_destroy(&done_mutex);
    pthread_cond_destroy(&cond_exit);
}
