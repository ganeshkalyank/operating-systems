#include <pthread.h>
#include <stdio.h>

volatile int flag[2];
volatile int turn;

void lock(int i);
void unlock(int i);

void *thread(void *arg) {
    int i = (int)arg;
    while (1) {
        lock(i);

        printf("Thread %d is in the critical section.\n", i);

        unlock(i);
    }
    return NULL;
}

void lock(int i) {
    flag[i] = 1;
    turn = 1 - i;
    while (flag[1 - i] && turn == 1 - i) {}
}

void unlock(int i) {
    flag[i] = 0;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread, (void *)0);
    pthread_create(&t2, NULL, thread, (void *)1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
