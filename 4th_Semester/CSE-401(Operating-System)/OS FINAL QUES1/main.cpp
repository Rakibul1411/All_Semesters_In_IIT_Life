#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>
#include <mutex>
#include <condition_variable>

int num_slices = 0;
int S ;
std::mutex mutex;
std::condition_variable pizza_ready;
sem_t pizza;     // Semaphore for the number of available pizza slices
sem_t deliver;   // Semaphore to signal the delivery thread
bool order_in_progress = false;

void student_thread(int id) {
    while (true) {
        sem_wait(&pizza);
        std::unique_lock<std::mutex> lock(mutex);
        if (num_slices == 0) {
            if (!order_in_progress) {
                order_in_progress = true;
                std::cout << "Student " << id << " Finds No Pizza and Orders a New One.\n";
                sem_post(&deliver);
            }
            std::cout << "Student " << id << " is Going To Sleep Until New Pizza Arrives.\n";
            pizza_ready.wait(lock, []{ return num_slices > 0; });
        }

        num_slices--;
        std::cout << "Student " << id << " is Eating a Slice of Pizza. Slices Left: " << num_slices << std::endl;
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void delivery_thread() {
    while (true) {
        sem_wait(&deliver);

        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Simulate pizza delivery time

        std::unique_lock<std::mutex> lock(mutex);
        num_slices = S;
        order_in_progress = false;
        std::cout << "Pizza Delivered with " << num_slices << " Slices." << std::endl;
        lock.unlock();

        pizza_ready.notify_all();

        for (int i = 0; i < S; ++i) {
            sem_post(&pizza);
        }
    }
}

int main() {
    int num_students;
    printf("Enter Number of Students: ");
    scanf("%d", &num_students);

    printf("Enter Number of Slices: ");
    scanf("%d", &S);

    sem_init(&pizza, 0, 0);
    sem_init(&deliver, 0, 1);

    std::vector<std::thread> students;
    for (int i = 0; i < num_students; ++i) {
        students.push_back(std::thread(student_thread, i + 1));
    }

    std::thread delivery(delivery_thread);

    for (auto& student : students) {
        student.join();
    }
    delivery.join();

    sem_destroy(&pizza);
    sem_destroy(&deliver);

    return 0;
}
