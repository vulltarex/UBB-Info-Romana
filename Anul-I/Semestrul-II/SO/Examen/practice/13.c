#include <semaphore.h>

sem_t s;

void* person(void* args){
    sem_wait(&s);
    printf("voting ...\n");
    sem_post(&s);
    return NULL;
}
 
int main(){
    pthread_t t[100];
    sem_init(&s, 0, 3);
    for(int i=0;i<100;i++){
        pthread_create(&t[i], NULL, person, NULL);
    }
    
    for(int i=0;i<100;i++){
        pthread_join(t[i], NULL);
    }
    sem_destroy(&s);
    
    return 0;
}
