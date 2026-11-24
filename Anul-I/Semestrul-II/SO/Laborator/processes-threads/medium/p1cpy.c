#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct {
    int tid;
    int start;
    int end;
    int* a;
    long long partial[10];
}ThreadArgs;

void* worker(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;

    for(int i = args->start; i < args->end; i++) {
        args->partial[args->a[i]]++;
    }
    
    return NULL;
}

int main(void) {
    int n, T;

    if(scanf("%d %d", &n, &T) != 2){
        fprintf(stderr, "eroare la citire");
        return 1;
    }

    int* a = malloc(n * sizeof(int));
    pthread_t* threads = malloc(T * sizeof(pthread_t));
    ThreadArgs* args = malloc(T * sizeof(ThreadArgs));
    long long vect_frecv[10];
    for(int i = 0; i < 10; i++) vect_frecv[i] = 0;
    if(!a || !threads || !args){
        fprintf(stderr, "eroare la alocare\n");
        free(a);
        free(threads);
        free(args);
        return 1;
    }

    for(int tid = 0; tid < T; tid++) {
        args[tid].tid = tid;
        args[tid].start = tid * n / T;
        args[tid].end = (tid + 1) * n / T;
        args[tid].a = a;
        for (int i = 0; i < 10; i++) {
            args[tid].partial[i] = 0;
        }

        if(pthread_create(&threads[tid], NULL, worker, &args[tid]) != 0){
            fprintf(stderr, "eroare la creare threadului");
            free(a);
            free(threads);
            free(args);
            return 1;
        }
    }

    for (int tid = 0; tid < T; tid++) {
        pthread_join(threads[tid], NULL);
    }
    
    for(int tid = 0; tid < T; tid++) {
        for (int i = 0; i < 10; i++) {
            vect_frecv[i] += args[tid].partial[i];
        }
    }

    for (int i = 0; i < 10; i++) {
        printf("%d:%lld\n", i, vect_frecv[i]);
    }

    free(a);
    free(threads);
    free(args);

    return 0;
}

