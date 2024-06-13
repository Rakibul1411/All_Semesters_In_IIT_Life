#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex, rw_mutex;
int write_count = 0;

int shared_data;

void *reader(void *arg);
void *writer(void *arg);

int main() {

    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], nullptr, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], nullptr, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], nullptr);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], nullptr);
    }

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}

void *reader(void *arg) {
    int id = *(int *)arg;
    while (1) {
        sem_wait(&mutex);
        write_count++;
        if (write_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);
        sem_wait(&rw_mutex);
        printf("Reader %d reads the shared data: %d, readers count: %d\n", id, shared_data, write_count);
        sem_wait(&mutex);
        write_count--;
        if (write_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);
        sleep(rand()%5);
    }
    return nullptr;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    while (1) {
        sem_wait(&mutex);
        write_count++;
        if (write_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);
        shared_data = rand() % 100;
        printf("Writer %d writes the value %d in the shared data\n", id, shared_data);
        sem_post(&rw_mutex);
        sleep(rand()%5);
    }
    return nullptr;
}