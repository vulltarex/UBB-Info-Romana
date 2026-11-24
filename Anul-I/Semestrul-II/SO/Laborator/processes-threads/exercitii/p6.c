#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global_min = 2147483647;
int global_max = -2147483648;
pthread_mutex_t m;

typedef struct {
    int tid;
    int start;
    int end;
    int* a;
}ThreadArgs;

void* worker(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;

    for (int i = args->start; i < args->end; i++) {
        if (args->a[i] < global_min) {
            pthread_mutex_lock(&m);
            global_min = args->a[i];
            pthread_mutex_unlock(&m);
        }
        if (args->a[i] > global_max) {
            pthread_mutex_lock(&m);
            global_max = args->a[i];
            pthread_mutex_unlock(&m);
        }
    }

    return NULL;
}

int main(void) {
    int n, t;
    
    scanf("%d %d", &n, &t);

    int* a = malloc(n * sizeof(int));
    pthread_t* threads = malloc(t * sizeof(pthread_t));
    ThreadArgs* args = malloc(t * sizeof(ThreadArgs));

    if (!a || !threads || !args) {
        fprintf(stderr, "eroare la alocare");
        free(a);
        free(threads);
        free(args);
    }

    pthread_mutex_init(&m, NULL);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int tid = 0; tid < t; tid++) {
        args[tid].tid = tid;
        args[tid].start = n * tid / t;
        args[tid].end = n * (tid + 1) / t;
        args[tid].a = a;
        if(pthread_create(&threads[tid], NULL, worker, &args[tid]) != 0){
            fprintf(stderr, "eroare la creare thread");
            free(a);
            free(threads);
            free(args);
            pthread_mutex_destroy(&m);
            return 1;
        }
    }
    
    for(int tid = 0; tid < t; tid++) {
        pthread_join(threads[tid], NULL);
    }

    printf("Minim: %d\n", global_min);
    printf("Maxim: %d\n", global_max);
    pthread_mutex_destroy(&m);
    free(a);
    free(threads);
    free(args);

    return 0;
}
