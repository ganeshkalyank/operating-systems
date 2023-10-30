#include <pthread.h>
#include <semaphore.h>

sem_t customers;
sem_t barber;
sem_t seats;

int free_seats;

void *barber(void *arg) {
  while (1) {
    sem_wait(&customers);

    sem_wait(&seats);
    free_seats++;

    sem_post(&barber);

    sem_wait(&barber);

    sem_post(&seats);

    if (free_seats == 0) {
      sem_wait(&customers);
    }
  }
}

void *customer(void *arg) {
  while (1) {
    sem_wait(&seats);

    if (free_seats == 0) {
      sem_post(&seats);
      return NULL;
    }

    free_seats--;

    sem_post(&customers);

    sem_wait(&barber);

    sem_post(&seats);

    return NULL;
  }
}

int main() {
  sem_init(&customers, 0, 0);
  sem_init(&barber, 0, 0);
  sem_init(&seats, 0, 1);

  pthread_t barber_thread;
  pthread_create(&barber_thread, NULL, barber, NULL);

  pthread_t customer_threads[10];
  for (int i = 0; i < 10; i++) {
    pthread_create(&customer_threads[i], NULL, customer, NULL);
  }

  pthread_join(barber_thread, NULL);
  for (int i = 0; i < 10; i++) {
    pthread_join(customer_threads[i], NULL);
  }

  sem_destroy(&customers);
  sem_destroy(&barber);
  sem_destroy(&seats);

  return 0;
}
