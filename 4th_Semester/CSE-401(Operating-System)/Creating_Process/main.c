#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pid;

    switch (pid = fork()){
        case 0:
            printf("I am the child process: pid=%d\n", getppid());
            break;
        default:
            printf("I am the parent process: pid=%d, child pid=%d\n", getpid(), pid);
            break;
        case -1:
            perror("Fork");
            exit(1);
    }
    exit(0);
}