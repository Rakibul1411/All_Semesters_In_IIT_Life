#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("My process ID is: %d\n", getpid());
    exit(0);
}
