#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define BUFFER_SIZE 10

sem_t empty_count, full_count, mutex;

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void produce() {
  sem_wait(&empty_count);
  sem_wait(&mutex);

  buffer[in] = rand() % 100;
  in = (in + 1) % BUFFER_SIZE;

  sem_signal(&mutex);
  sem_post(&full_count);
}

void consume() {
  sem_wait(&full_count);
  sem_wait(&mutex);

  int item = buffer[out];
  out = (out + 1) % BUFFER_SIZE;

  sem_signal(&mutex);
  sem_post(&empty_count);

  printf("Consumed: %d\n", item);
}

void* producer_thread(void* arg) {
  while (1) {
    produce();
  }
}

void* consumer_thread(void* arg) {
  while (1) {
    consume();
  }
}

int main() {
  pthread_t producer_threads[2];
  pthread_t consumer_threads[2];

  sem_init(&empty_count, 0, BUFFER_SIZE);
  sem_init(&full_count, 0, 0);
  sem_init(&mutex, 0, 1);

  for (int i = 0; i < 2; i++) {
    pthread_create(&producer_threads[i], NULL, producer_thread, NULL);
    pthread_create(&consumer_threads[i], NULL, consumer_thread, NULL);
  }

  for (int i = 0; i < 2; i++) {
    pthread_join(producer_threads[i], NULL);
    pthread_join(consumer_threads[i], NULL);
  }

  sem_destroy(&empty_count);
  sem_destroy(&full_count);
  sem_destroy(&mutex);

  return 0;
}
