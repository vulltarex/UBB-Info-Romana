#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int tid;
    int start;
    int end;
    int* a;
    int* b;
    int* rez;
}ThreadArgs;

void* worker(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;

    for (int i = args->start; i < args->end; i++) {
        args->rez[i] = args->a[i] + args->b[i];
    }

    return NULL;
}

int main(void) {
    int r, c, t;
    scanf("%d %d %d", &r, &c, &t);

    int* a = malloc(r * c * sizeof(int));
    int* b = malloc(r * c * sizeof(int));
    pthread_t* threads = malloc(t * sizeof(pthread_t));
    ThreadArgs* args = malloc(t * sizeof(ThreadArgs));
    int* rez = malloc(r * c * sizeof(int));

    if (!a || !b || !threads || !args || !rez){
        fprintf(stderr, "eroare la alocare\n");
        free(a);
        free(b);
        free(threads);
        free(args);
        free(rez);
        return 1;
    }

    for (int i = 0; i < r * c; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < r * c; i++) {
        scanf("%d", &b[i]);
    }

    for (int tid = 0; tid < t; tid++) {
        args[tid].tid = tid;
        args[tid].start = tid * r * c /t;
        args[tid].end = (tid + 1) * r * c /t;
        args[tid].a = a;
        args[tid].b = b;
        args[tid].rez = rez;

        if (pthread_create(&threads[tid], NULL, worker, &args[tid]) != 0) {
            fprintf(stderr, "eroare la creare thread\n");
            free(a);
            free(b);
            free(threads);
            free(args);
            free(rez);
            return 1;
        }
    }

    for (int tid = 0; tid < t; tid++) {
        pthread_join(threads[tid], NULL);
    }

    for (int i = 0; i < r * c; i++){
        printf("%d ", rez[i]);
        if ((i + 1) % c == 0) {
            printf("\n");
        }
    }


    free(a);
    free(b);
    free(threads);
    free(args);
    free(rez);


    return 0;
}
