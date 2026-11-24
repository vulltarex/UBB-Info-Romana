#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    for(int i = 0; i < 2; i++){
   	 if(fork() == 0){
	     if(i == 0){
		if(fork() == 0){
		    printf("nepot: %d, parinte:%d\n", getpid(), getppid());
		    exit(0);
		}
		wait(0);
	     }
	     printf("proces: %d, parinte: %d\n", getpid(), getppid());
	     exit(0);
         }
    }
    for(int i = 0; i < 2; i++){
        wait(0);
    }
    return 0;
}
