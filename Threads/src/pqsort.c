#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pqsort.h"
#include "thread_pool.h"

struct Non_changeable {
    int max_depth;
    int* done;
    int* arr;
    struct ThreadPool* pool;
    pthread_mutex_t *done_mutex;
    pthread_cond_t *cond_exit;
    struct squeue* queue;
};
    
struct Args {
    int depth;
    int left;
    int right;
    struct Task task;
    struct Non_changeable* n;
};

void pqsort(void* a);

struct Task* create_args(int left, int right, struct Args *ar){
    struct Args* args = malloc(sizeof(struct Args));
    create_task(&args->task);
    args->n = ar->n;
    args->left = left;
    args->right = right;
    args->task.arg = args;
    return &args->task;
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
    if(args->depth >= args->n->max_depth){
        qsort(args->n->arr+left, (right-left), sizeof (int), (int(*) (const void *, const void *)) comp);
        pthread_mutex_lock(args->n->done_mutex);
        *args->n->done -= (right-left);
        if(*args->n->done == 0) pthread_cond_signal(args->n->cond_exit);
        pthread_mutex_unlock(args->n->done_mutex);
    }else{
        if(right - left == 1) {
            pthread_mutex_lock(args->n->done_mutex);
            (*args->n->done)--;
            if(*args->n->done == 0) pthread_cond_signal(args->n->cond_exit);  
            pthread_mutex_unlock(args->n->done_mutex);
        }
        if(right - left > 1) {
            struct Task* task = create_args(left, right, args);
            thpool_submit(args->n->pool, task);
        }   
    }
}

int comp (const int *i, const int *j){
    if(*i > *j){
        return 1;
    }
    if(*i == *j){
        return 0;
    }
    return -1;
}

void pqsort(void* a){
    struct Args* args = a;
    int new_border = q_partition(args->left, args->right, args->n->arr);
    args->depth++;
    submit_qsort_task(args->left, new_border, args);
    submit_qsort_task(new_border, args->right, args);
    squeue_push(args->n->queue, (struct list_node*) (args));
}

struct Task* create_task(struct Task* task){
    task->f = pqsort;
    task->complete = 0;
    pthread_mutex_init(&task->mutex, NULL);
    pthread_cond_init(&task->cond, NULL);
    return task;
}

void destroy_args(struct Args* args){
    pthread_mutex_destroy(&args->task.mutex);
    pthread_cond_destroy(&args->task.cond);
    free(args);    
}

void sort_array(int depth, int max_depth, int* x, int N, struct ThreadPool* pool){
    int* done = &N;
    pthread_mutex_t done_mutex;
    pthread_cond_t cond_exit;
    pthread_mutex_init(&done_mutex, NULL);
    pthread_cond_init(&cond_exit, NULL);
    
    struct Args args;
    struct squeue queue;
    struct Non_changeable n;
    
    squeue_init(&queue);
    n.done = done;
    n.max_depth = max_depth;
    n.arr = x;
    n.pool = pool;
    n.done_mutex = &done_mutex;
    n.cond_exit = &cond_exit;
    n.queue = &queue;

    args.depth = depth;
    args.left = 0;
    args.right = N;
    args.n = &n;

    submit_qsort_task(0, N, &args);
    pthread_mutex_lock(&done_mutex);
    while(*done > 0){
        pthread_cond_wait(&cond_exit, &done_mutex);
    }
    pthread_mutex_unlock(&done_mutex);
    while(queue.queue.size > 0){
        struct list_node* node = squeue_pop(&queue);
        struct Args* args = (struct Args*) node;
        destroy_args(args);
    }
    squeue_finit(&queue);
    pthread_mutex_destroy(&done_mutex);
    pthread_cond_destroy(&cond_exit);
}
