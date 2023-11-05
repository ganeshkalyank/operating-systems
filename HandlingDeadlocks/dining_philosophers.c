#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

sem_t chopsticks[NUM_PHILOSOPHERS];
sem_t mutex;

void philosopher(void *arg) {
  int philosopher_id = *(int *)arg;

  while (1) {
    printf("Philosopher %d is thinking\n", philosopher_id);

    sem_wait(&mutex);

    if (sem_trywait(&chopsticks[(philosopher_id + 1) % NUM_PHILOSOPHERS]) == 0) {
      if (sem_trywait(&chopsticks[philosopher_id]) == 0) {
        printf("Philosopher %d is eating\n", philosopher_id);

        sem_post(&chopsticks[philosopher_id]);
        sem_post(&chopsticks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);

        sem_post(&mutex);
      } else {
        sem_post(&chopsticks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
        sem_post(&mutex);
      }
    } else {
      sem_post(&mutex);
    }
  }
}

int main() {
  pthread_t philosopher_threads[NUM_PHILOSOPHERS];
  int philosopher_ids[NUM_PHILOSOPHERS];

  sem_init(&mutex, 0, 1);

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    sem_init(&chopsticks[i], 0, 1);
  }

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    philosopher_ids[i] = i;
    pthread_create(&philosopher_threads[i], NULL, philosopher, &philosopher_ids[i]);
  }

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(philosopher_threads[i], NULL);
  }

  return 0;
}
