#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myThreadFun() {
    sleep(1);
    printf("SASTRA University \n");
    return NULL;
}

int main() {
    pthread_t thread_id;
    printf("Before thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After thread\n");
    return 0;
}
