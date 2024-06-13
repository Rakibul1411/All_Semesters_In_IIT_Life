#include <iostream>
#include <thread>
#include <csignal>
#include <cstdlib>
#include <atomic>
#include <chrono>
using namespace std;

atomic<bool> running(true);

void signal_handler(int signal) {
    if (signal == SIGINT) {
        cout << "\nSIGINT caught, terminating program..." << endl;
        running = false;
    }
}

void thread_task() {
    while (running) {
        cout << "Thread is running..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        //sleep(1);
    }
    cout << "Thread terminating gracefully..." << endl;
}

int main() {
    signal(SIGINT, signal_handler);
    // Start the worker thread
    thread worker(thread_task);
    
    // Main thread waits for the signal
    while (running) {
        this_thread::sleep_for(chrono::seconds(1));
        //sleep(1);
    }

    // Wait for the worker thread to finish
    if (worker.joinable()) {
        worker.join();
    }

    cout << "Main program terminating gracefully..." << endl;
    return 0;
}

