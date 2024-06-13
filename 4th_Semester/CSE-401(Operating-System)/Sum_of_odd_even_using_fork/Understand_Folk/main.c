#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Hello, World!\n");

    printf("--------\n");

    fork();
    printf("1\n");
    printf("2\n");

     exit(0);
}
