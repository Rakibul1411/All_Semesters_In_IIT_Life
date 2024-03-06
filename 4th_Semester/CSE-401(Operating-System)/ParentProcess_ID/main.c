#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("My process ID is: %d\n", getpid());
    printf("My parent's process ID is: %d\n", getppid());
    exit(0);
}
