/*
  An alternative solution to the
  Dining Philosophers problem using an arbitrator.
  This way it can be guaranteed that an individual philosopher
  can only pick up both or none of the chopsticks.
  We can imagine a waiter performing this service.
  The waiter gives permission to only one philosopher at a time
  until she picks up both chopsticks. Putting down a chopstick
  is always allowed. The waiter can be implemented in code as a mutex.
  This solution introduces a central entity (arbitrator) and can also
  result in reduced parallelism. If one philosopher is eating and
  another request a fork, all other philosophers must wait until
  this request is fulfilled, even if other chopsticks are still
  available to them. */


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
sem_t arbitrator;

void *philosopher(void *arg) {
    int philosopher_id = *(int*) arg;
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", philosopher_id);
        usleep(rand() % 1000000);

        // Waiting for forks
        sem_wait(&arbitrator);

        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);

        // Eating
        printf("Philosopher %d is eating.\n", philosopher_id);
        usleep(rand() % 1000000);

        // Freeing forks
        sem_post(&forks[right_fork]);
        sem_post(&forks[left_fork]);

        // Signaling arbitrator
        sem_post(&arbitrator);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    sem_init(&arbitrator, 0, NUM_PHILOSOPHERS - 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
