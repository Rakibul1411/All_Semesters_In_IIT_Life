#include <iostream>
using namespace std;
#include <pthread.h>
#include <unistd.h>

#define N 5 //number of philosophers (also the number of forks)
#define MIN_THINK_TIME  5
#define MAX_THINK_TIME 10
#define MIN_EAT_TIME  5
#define MAX_EAT_TIME 10
pthread_mutex_t forks[N];
pthread_mutex_t sc_lock;

void think(int);
void eat(int);
void pickForks(int);
void releaseForks(int);
void* philosopher(void*);

void pickForks(int pNumber)
{
    if (pNumber < N - 1)
    {
        //All threads except the last thread (philosopher) will first pick the left fork and then the right fork.
        pthread_mutex_lock(&forks[pNumber]);
        pthread_mutex_lock(&forks[pNumber + 1]);
    }
    else
    {
        //the last thread (philosopher) will first pick the right fork and then the left fork.
        pthread_mutex_lock(&forks[0]);
        pthread_mutex_lock(&forks[pNumber]);
    }
}

void releaseForks(int pNumber)
{
    pthread_mutex_unlock(&forks[pNumber]);
    pthread_mutex_unlock(&forks[(pNumber + 1) % N]);
}

void eat(int pNumber)
{
    pthread_mutex_lock(&sc_lock);
    cout << "Philosopher no= " << pNumber << " is eating." << endl;
    pthread_mutex_unlock(&sc_lock);

    int time = rand() % MAX_EAT_TIME + MIN_EAT_TIME;
    sleep(time);

    pthread_mutex_lock(&sc_lock);
    cout << "Philosopher no= " << pNumber << " has finished eating." << endl;
    pthread_mutex_unlock(&sc_lock);
}

void think(int pNumber)
{
    pthread_mutex_lock(&sc_lock);
    cout << "Philosopher no= " << pNumber << " is thinking." << endl;
    pthread_mutex_unlock(&sc_lock);

    int time = rand() % MAX_THINK_TIME + MIN_THINK_TIME;
    sleep(time);

    pthread_mutex_lock(&sc_lock);
    cout << "Philosopher no= " << pNumber << " has finished thinking." << endl;
    pthread_mutex_unlock(&sc_lock);
}

void* philosopher(void* arg)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, nullptr);

    int pNumber = *((int*)arg); //philosopher number

    while (true)
    {
        think(pNumber);
        pickForks(pNumber);
        eat(pNumber);
        releaseForks(pNumber);
    }

}

int main()
{
    for (int i = 0; i < N; i++)
    {
        if (pthread_mutex_init(&forks[i], nullptr) != 0)
        {
            cout << "Error initializing fork mutex no. "<<i<<"!" << endl;
            return 1;
        }
    }
    if (pthread_mutex_init(&sc_lock, nullptr) != 0)
    {
        cout << "Error initializing sc_lock mutex." << endl;
        return 1;
    }

    pthread_t tid[N];
    int arg[N];
    for (int i = 0; i < N; i++)
    {
        arg[i] = i;
        pthread_create(&tid[i], nullptr, &philosopher, &arg[i]);
        pthread_detach(tid[i]);
    }

    char a = 0;
    while (a != 'e' && a!='E'){ //If the user presses key 'e', then the main thread will terminate all philosopher threads.
        cin >> a;
    }


    for (auto & i : tid)
    {
        pthread_cancel(i);  //sending a signal to all philosopher threads to terminate.
    }

    for (auto & fork : forks)
    {
        pthread_mutex_destroy(&fork);
    }
    pthread_mutex_destroy(&sc_lock);

    return 0;
}