#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <semaphore.h>
#include <pthread.h>

int NumberOfStudent;
int NumberOfSlice = 0;
int S;
sem_t pizza;
sem_t deliver;
sem_t mutex;
bool deliveryProcess = true;

void *delivery(void *arg){
    while(1){
        sem_wait(&deliver);

        printf("Pizza is Being Prepared.....\n\n");
        sleep(5);
        printf("Pizza is Delivered\n\n");

        sem_wait(&mutex);
        NumberOfSlice += S;
        for(int i = 0; i < S; i++){
            sem_post(&pizza); // Signal that slices are available
        }
        deliveryProcess = false;
        sem_post(&mutex);
    }
}


void *student(void *arg){
    int id = *(int *)arg;
    bool flag;

    while(1){
        flag = true;
        while(NumberOfSlice == 0){
            if(flag){
                printf("Student %d is Sleeping\n\n", id);
                flag = false;
            }
        }
        sem_wait(&pizza); // Wait for a slice to be available

        sem_wait(&mutex);
        if(NumberOfSlice > 0){
            NumberOfSlice--;
            printf("Student %d is Eating Pizza and Studying. Remaining Pizza Slices: %d\n\n", id, NumberOfSlice);
        }
        if(NumberOfSlice == 0){
            if(!deliveryProcess){
                deliveryProcess = true;
                sem_post(&deliver); // Signal for pizza delivery
            }
        }
        sem_post(&mutex);

        sleep((rand() % 3) + 1);
    }
}


int main(){
    srand(time(nullptr));

    sem_init(&pizza, 0, 0);
    sem_init(&deliver, 0, 1);
    sem_init(&mutex, 0, 1);

    printf("Enter Number of Students: ");
    scanf("%d", &NumberOfStudent);

    printf("Enter Number of Slices: ");
    scanf("%d", &S);

    printf("\n");

    pthread_t students[NumberOfStudent];
    pthread_t pizza_delivery;
    int studentID[NumberOfStudent];

    for(int i = 0; i < NumberOfStudent; i++){
        studentID[i] = i + 1;
    }

    for(int i = 0; i < NumberOfStudent; i++){
        pthread_create(&students[i], nullptr, student, &studentID[i]);
    }

    pthread_create(&pizza_delivery, nullptr, delivery, nullptr);

    for(int i = 0; i < NumberOfStudent; i++){
        pthread_join(students[i], nullptr);
    }

    pthread_join(pizza_delivery, nullptr);

    sem_destroy(&pizza);
    sem_destroy(&deliver);
    sem_destroy(&mutex);
    return 0;
}


