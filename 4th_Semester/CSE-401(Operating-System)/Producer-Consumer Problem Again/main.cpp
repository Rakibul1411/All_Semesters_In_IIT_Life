#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define buffer_size 10

sem_t empty,mutex,full;
int buffer[buffer_size],in,out;

void *produce(void *param);
void *consume(void *param);

int main(){
    sem_init(&empty,0,buffer_size);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    int thread_size=1;
    pthread_t producer,consumer;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    int i;
    pthread_create(&producer,&attr,produce,NULL);
    pthread_create(&consumer,&attr,consume,NULL);
    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}

void *produce(void *param){
    int item;
    while (1){
        item=rand()%20;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in]=item;
        printf("Produced item %d at index %d\n",item,in);
        in=(in+1)%buffer_size;
        sem_post(&mutex);
        sem_post(&full);
        sleep(rand()%2);
    }

}

void *consume(void *param){
    int item;
    while(1){
        sem_wait(&full);
        sem_wait(&mutex);
        item=buffer[out];
        printf("Consumed item %d from from %d\n",item,out);
        out=(out+1)%buffer_size;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(rand()%2);
    }
}