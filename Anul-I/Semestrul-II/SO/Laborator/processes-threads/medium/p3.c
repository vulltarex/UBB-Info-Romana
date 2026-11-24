#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int tid;
    int start;
    int end;
    char* a;
    int local;
}ThreadArgs;

void* worker(void* arg){
    ThreadArgs* args = (ThreadArgs*)arg;

    for(int i = args->start; i < args->end; i++){
        if(args->a[i] != ' '  && (i == 0 || args->a[i - 1] == ' ')) {
            args->local++;
        }
    }

    return NULL;
}

int main(void) {
    int t;

    scanf("%d", &t);
    getchar();
    char a[1000];
    if(fgets(a, 1000, stdin) == NULL) {
        fprintf(stderr, "eroare la citire\n");
        return 1;
    }
    int size;
    for (size = 0; a[size] != '\n'; size++);
    a[size] = '\0';
    
    pthread_t* threads = malloc(t * sizeof(pthread_t));
    ThreadArgs* args = malloc(t * sizeof(ThreadArgs));
    if(!threads || !args) {
        fprintf(stderr, "eroare la alocare\n");
        free(threads);
        free(args);
        return 1;
    }

    for (int tid = 0; tid < t; tid++) {
        args[tid].tid = tid;
        args[tid].start = size * tid / t;
        args[tid].end = size * (tid + 1) / t;
        args[tid].a = a;
        args[tid].local = 0;

        if (pthread_create(&threads[tid], NULL, worker, &args[tid]) != 0){
            fprintf(stderr, "eroare la creare thread\n");
            free(threads);
            free(args);
            return 1;
        }
    }
    
    for (int tid = 0; tid < t; tid++) {
        pthread_join(threads[tid], NULL);
    }

    int total = 0;

    for(int tid = 0; tid < t; tid++) {
        total += args[tid].local;
    }

    printf("%d\n", total);

    free(threads);
    free(args);

    return 0;
}
