#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void* f(void* arg){
    printf("sunt thread-ul cu numarul: %d\n", *(int*)arg);
    return NULL;
}

int main(){
    pthread_t t[4];
    int a[4];
    for(int i = 0; i < 4; i++){
        a[i] = i;
        pthread_create(&t[i], NULL, f, &a[i]);
    }

    for(int i = 0; i < 4; i++){
        pthread_join(t[i], NULL);
    }

    return 0;
}
