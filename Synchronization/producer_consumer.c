#include <pthread.h>
#include <semaphore.h>

sem_t mutex;
sem_t wrt;

int readcount = 0;
int writecount = 0;

void *reader(void *arg) {
    sem_wait(&wrt);

    readcount++;

    if (readcount == 1) {
        sem_wait(&mutex);
    }

    readcount--;

    if (readcount == 0) {
        sem_post(&mutex);
    }

    sem_post(&wrt);

    return NULL;
}

void *writer(void *arg) {
    sem_wait(&mutex);

    writecount++;

    writecount--;

    sem_post(&mutex);

    return NULL;
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_t reader_threads[10];
    pthread_t writer_threads[5];

    for (int i = 0; i < 10; i++) {
        pthread_create(&reader_threads[i], NULL, reader, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&writer_threads[i], NULL, writer, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
