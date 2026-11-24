#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int p[2];
    pipe(p);
    if(fork() == 0){
        close(p[0]);
        dup2(p[1],1);
        close(p[1]);
        execlp("ls", "ls", "-l", NULL);
        exit(0);
    }
    if(fork() == 0){
        close(p[1]);
        dup2(p[0],0);
        close(p[0]);
        execlp("grep", "grep", "txt", NULL);
        exit(0);
    }
    close(p[0]);
    close(p[1]);
    for(int i = 0; i < 2; i++){
        wait(0);
    }
    return 0;
}
