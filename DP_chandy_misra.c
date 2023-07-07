/* C implementation of solution to the
   Dining Philosophers problem using
   Chandy/Misra algorithm. The Chandy/Misra
   solution was proposed in 1984 to allow a
   solution to the problem for arbitrary agents
   (numbered P1...Pn) that contend for an arbitrary
   number of resources. It is also completely
   distributed and requires no central authority after
   initialization. However, it violates the
   requirement that "philosophers do not speak to
   each other". In this case,they use request messages.

   The algorithm can be broken down as follows:
   1) For every pair of philosophers contending for
   the resource, create a fork and give it to the
   philosopher with the lower ID (n for agent Pn). Each
   fork can be either "dirty" or "clean". Initially, all
   forks are dirty.
   2) When a philosopher wants to use a set of resources
   (i.e. eat),that philosopher must obtain the forks
   from their contending neighbors, For all such forks
   the philosopher does not have, they send a request message.
   3) When a philosopher with a fork receives a request
   message, they keep the fork if it is clean, but give it
   up when it is dirty. If the philosopher passes the fork
   on, they clean it before doing so.
   4) After a philosopher is done eating, all their forks
   become dirty. If another philosopher had previously
   requested one of the forks, the philosopher that has
   just finished eating cleans the fork and sends it.

   This solution allows for a large degree of concurrency, and
   will solve an arbitrarily large problem. It also solves the
   starvation problem. The clean/dirty labels act as a way of
   giving preference to the most "starved" processes and a
   disadvantage to processes that have just "eaten". */



#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define N 5  // Number of philosophers

enum {THINKING, HUNGRY, EATING} state[N];
sem_t mutex;
sem_t self[N];

void* philosopher(void* arg) {
    int i = *(int*)arg;
    while (1) {
        printf("Philosopher %d is thinking\n", i+1);
        sleep(rand() % 2);
        take_fork(i);
        printf("Philosopher %d is eating\n", i+1);
        sleep(rand() % 2);
        put_fork(i);
    }
}

void take_fork(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    test(i);
    sem_post(&mutex);
    sem_wait(&self[i]);
}

void put_fork(int i) {
    sem_wait(&mutex);
    state[i] = THINKING;
    test((i + N - 1) % N);
    test((i + 1) % N);
    sem_post(&mutex);
}

void test(int i) {
    if (state[i] == HUNGRY && state[(i + N - 1) % N] != EATING && state[(i + 1) % N] != EATING) {
        state[i] = EATING;
        sem_post(&self[i]);
    }
}

int main() {
    int i;
    pthread_t philosophers[N];
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++) {
        sem_init(&self[i], 0, 0);
    }

    for (i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &i);
        printf("Philosopher %d is thinking\n", i+1);
    }

    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
