#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int tid;
    int start;
    int end;
    int* a;
    long long* partial;
}ThreadArgs;

void* worker(void* arg){
    ThreadArgs* args = (ThreadArgs*)arg;

    long long local = 0;

    for(int i = args->start; i < args->end; i++) {
        local += args->a[i];
    }

    args->partial[args->tid] = local;
    return NULL;
}

int main(void) {
    int n, T;

    scanf("%d %d", &n, &T);

    int *a = malloc(n * sizeof(int));
    pthread_t* threads = malloc(T * sizeof(pthread_t));
    ThreadArgs* args = malloc(T * sizeof(ThreadArgs));
    long long* partial = calloc(T * sizeof(long long));
    
    if(!a || !threads || !args || !partial) {
        fprintf(stderr, "Eroare la alocare\n");
        free(a);
        free(threads);
        free(args);
        free(partial);
        return 1;
    }

    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int tid = 0; tid < T; tid++) {
        args[tid].tid = tid;
        args[tid].start = n * tid / T;
        args[tid].end = n * (tid + 1) / T;
        args[tid].a = a;
        args[tid].partial = partial;

        if (pthread_create(&threads[tid], NULL, worker, &args[tid]) != 0) {
            fprintf(stderr, "failed to create thread");
            free(a);
            free(threads);
            free(args);
            free(partial);
            return 1;
        }
    }
    
    for (int tid = 0; tid < T; tid++) {
        pthread_join(threads[tid], NULL);
    }

    long long total = 0;

    for(int tid = 0; tid < T; tid++) {
        total += partial[tid];
    }

    printf("%lld\n", total);

    free(a);
    free(threads);
    free(args);
    free(partial);

    return 0;
}
