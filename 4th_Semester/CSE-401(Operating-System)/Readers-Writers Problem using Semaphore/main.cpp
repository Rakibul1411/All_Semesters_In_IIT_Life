#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <cstdio>

sem_t resource_access;
sem_t reader_count_access;
int resource_counter = 1;
int active_readers = 0;

void* writer_thread(void* writer_number) {
    sem_wait(&resource_access);  // Wait for resource access to write

    resource_counter *= 2;
    printf("Writer %d modified resource_counter to %d\n", *((int*)writer_number), resource_counter);

    sem_post(&resource_access);  // Release resource access after writing
    return nullptr;
}

void* reader_thread(void* reader_number) {
    sem_wait(&reader_count_access);  // Ensure exclusive access to active_readers

    active_readers++;
    if (active_readers == 1) {
        sem_wait(&resource_access);  // If first reader, lock resource access
    }

    sem_post(&reader_count_access);  // Release exclusive access to active_readers

    printf("Reader %d: read resource_counter as %d\n", *((int*)reader_number), resource_counter);

    sem_wait(&reader_count_access);  // Ensure exclusive access to active_readers

    active_readers--;
    if (active_readers == 0) {
        sem_post(&resource_access);  // If last reader, unlock resource access
    }

    sem_post(&reader_count_access);  // Release exclusive access to active_readers
    return nullptr;
}

int main() {
    sem_init(&resource_access, 0, 1);  // Initialize semaphore for resource access
    sem_init(&reader_count_access, 0, 1);  // Initialize semaphore for reader count access

    pthread_t readers[10], writers[5];
    int reader_numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int writer_numbers[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 10; i++) {
        pthread_create(&readers[i], nullptr, reader_thread, (void*)&reader_numbers[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&writers[i], nullptr, writer_thread, (void*)&writer_numbers[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(readers[i], nullptr);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(writers[i], nullptr);
    }

    sem_destroy(&resource_access);  // Destroy semaphore for resource access
    sem_destroy(&reader_count_access);  // Destroy semaphore for reader count access

    return 0;
}
