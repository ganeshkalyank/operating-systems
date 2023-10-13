#include <pthread.h>
#include <semaphore.h>

int buffer[10];
int in = 0, out = 0;

sem_t mutex, full, empty;

void *producer(void *args) {
    int count = 0;
    while (count < 100) {
        sem_wait(&empty);

        sem_wait(&mutex);

        buffer[in] = rand() % 100;
        in = (in + 1) % 10;

        sem_post(&mutex);

        sem_post(&full);

        count++;
    }
}

void *consumer(void *args) {
    int count = 0;
    while (count < 100) {
        sem_wait(&full);

        sem_wait(&mutex);

        int item = buffer[out];
        out = (out + 1) % 10;

        sem_post(&mutex);

        sem_post(&empty);

        printf("Consumed item: %d\n", item);
        count++;
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 10);

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
