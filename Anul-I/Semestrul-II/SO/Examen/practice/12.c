int n = 0;
pthread_mutex_t m; 
void* f(void* v){
        pthread_mutex_lock(&m);
        if(n < 500) {
            n++;
        }
        pthread_mutex_unlock(&m);
        return NULL;
}
 
int main(){
    pthread_t t;
    pthread_mutex_init(&m);
    pthread_create(&t, NULL, f, NULL);
    pthread_join(t, NULL);
    pthread_mutex_destroy(&m);
    return 0;
}

