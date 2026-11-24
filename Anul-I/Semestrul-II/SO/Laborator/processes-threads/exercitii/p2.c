#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int p[2];
    pipe(p);
    if(fork() == 0){
        close(p[1]);
        int numar;
        read(p[0], &numar, sizeof(int));
        numar *= 2;
        printf("nr dublat: %d\n", numar);
        close(p[0]);
        exit(0);
    }
    else {
        close(p[0]);
        int numar = rand() % 16000;
        printf("nr init: %d\n", numar);
        write(p[1], &numar, sizeof(int));
        close(p[1]);
        wait(0);
    }
    return 0;
}
