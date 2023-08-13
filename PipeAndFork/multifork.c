#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    fork();
    printf("1\n");
    fork();
    printf("2\n");
    fork();
    printf("3\n");
    return 0;
}
