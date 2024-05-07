#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <cstdio>

sem_t resource_access;

sem_t reader_count_access;

int resource_counter = 1;

int active_readers = 0;

void *writer_thread(void *writer_number)
{
    sem_wait(&resource_access);

    resource_counter *= 2;
    printf("Writer %d modified resource_counter to %d\n", *((int *)writer_number), resource_counter);

    sem_post(&resource_access);
}

void *reader_thread(void *reader_number)
{
    sem_wait(&reader_count_access);

    active_readers++;
    if (active_readers == 1) {
        sem_wait(&resource_access);
    }

    sem_post(&reader_count_access);

    printf("Reader %d: read resource_counter as %d\n", *((int *)reader_number), resource_counter);

    sem_wait(&reader_count_access);

    active_readers--;
    if (active_readers == 0) {
        sem_post(&resource_access);
    }

    sem_post(&reader_count_access);
}

int main()
{
    sem_init(&resource_access, 0, 1);
    sem_init(&reader_count_access, 0, 1);

    pthread_t readers[10], writers[5];
    int reader_numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int writer_numbers[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 10; i++) {
        pthread_create(&readers[i], NULL, reader_thread, (void *)&reader_numbers[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&writers[i], NULL, writer_thread, (void *)&writer_numbers[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&resource_access);
    sem_destroy(&reader_count_access);

    return 0;
}
