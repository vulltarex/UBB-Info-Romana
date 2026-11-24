#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int bilete = 10000;

void* f(void* arg){
    while(1){
        pthread_mutex_lock((pthread_mutex_t*)arg);
        if(bilete > 0){
            bilete--;
            pthread_mutex_unlock((pthread_mutex_t*)arg);
        }
        if(bilete == 0){
            pthread_mutex_unlock((pthread_mutex_t*)arg);
            break;
        }
    }
    return NULL;
}

int main(){
    pthread_mutex_t m;
    pthread_t t[5];
    pthread_mutex_init(&m, NULL);
    for(int i = 0; i < 5; i++){
        pthread_create(&t[i], NULL, f, &m);
    }

    for(int i = 0; i < 5; i++){
        pthread_join(t[i], NULL);
    }
    
    pthread_mutex_destroy(&m);
    printf("bilete ramase: %d\n", bilete);

    return 0;
}
