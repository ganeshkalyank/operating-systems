#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        printf("Current PID (Child): %d, Parent PID: %d\n",getpid(),getppid());
    } else if (pid > 0) {
        printf("Current PID (Parent): %d, Parent PID: %d\n",getpid(),getppid());
    } else {
        fprintf(stderr,"Error: %d\n",errno);
    }
    return 0;
}
