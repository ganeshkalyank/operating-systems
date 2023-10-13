#include <pthread.h>
#include <semaphore.h>

int data;

sem_t mutex, wrt;
int readcount;

void *reader(void *args) {
    while (1) {
        sem_wait(&mutex);

        readcount++;

        if (readcount == 1) {
            sem_wait(&wrt);
        }

        sem_post(&mutex);

        printf("Reader read: %d\n", data);

        sem_wait(&mutex);

        readcount--;

        if (readcount == 0) {
            sem_post(&wrt);
        }

        sem_post(&mutex);
    }
}

void *writer(void *args) {
    while (1) {
        sem_wait(&wrt);

        data = rand() % 100;

        sem_post(&wrt);
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    readcount = 0;

    pthread_t reader_thread1, reader_thread2, writer_thread;
    pthread_create(&reader_thread1, NULL, reader, NULL);
    pthread_create(&reader_thread2, NULL, reader, NULL);
    pthread_create(&writer_thread, NULL, writer, NULL);

    pthread_join(reader_thread1, NULL);
    pthread_join(reader_thread2, NULL);
    pthread_join(writer_thread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
