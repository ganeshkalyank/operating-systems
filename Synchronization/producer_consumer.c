#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

sem_t empty_count;
sem_t full_count;
sem_t mutex;

int buffer[BUFFER_SIZE];

int prod_count = 0;
int con_count = 0;

void produce() {
  sem_wait(&empty_count);
  sem_wait(&mutex);

  buffer[prod_count] = prod_count;
  prod_count++;

  sem_post(&mutex);
  sem_post(&full_count);
}

void consume() {
  sem_wait(&full_count);
  sem_wait(&mutex);

  int item = buffer[con_count];
  con_count++;

  sem_post(&mutex);
  sem_post(&empty_count);

  printf("Consumed item: %d\n", item);
}

void* producer_thread(void* arg) {
  while (prod_count < 100) {
    produce();
  }

  return NULL;
}

void* consumer_thread(void* arg) {
  while (con_count < 100) {
    consume();
  }

  return NULL;
}

int main() {
  sem_init(&empty_count, 0, BUFFER_SIZE);
  sem_init(&full_count, 0, 0);
  sem_init(&mutex, 0, 1);

  pthread_t producer_threads[10];
  pthread_t consumer_threads[10];

  for (int i = 0; i < 10; i++) {
    pthread_create(&producer_threads[i], NULL, producer_thread, NULL);
    pthread_create(&consumer_threads[i], NULL, consumer_thread, NULL);
  }

  for (int i = 0; i < 10; i++) {
    pthread_join(producer_threads[i], NULL);
    pthread_join(consumer_threads[i], NULL);
  }

  return 0;
}
