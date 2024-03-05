#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
sem_t empty, full;
int in = 0, out = 0;
void *producer(void *arg) {
    int item = rand() % 100; 
    sem_wait(&empty); 
    buffer[in] = item;
    printf("Produced item: %d\n", item);
    in = (in + 1) % BUFFER_SIZE;
    sem_post(&full); 
    pthread_exit(NULL);
}
void *consumer(void *arg) {
    sem_wait(&full); 
    int item = buffer[out];
    printf("Consumed item: %d\n", item);
    out = (out + 1) % BUFFER_SIZE;
    sem_post(&empty); 
    pthread_exit(NULL);
}
int main() {
    pthread_t prod, cons;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
