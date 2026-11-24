#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    while (wait(NULL) > 0) {
        if (fork() == 0) {
            exit(0);
        }
    }
    return 0;
}
