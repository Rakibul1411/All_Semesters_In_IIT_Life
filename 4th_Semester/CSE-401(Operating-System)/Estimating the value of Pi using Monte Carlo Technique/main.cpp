#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <pthread.h>

using namespace std;
unsigned int seed;

double randomNumberGenerator() {
    return rand_r(&seed) / (double)RAND_MAX;
}

void* calculatePi(void* arg) {
    auto totalCount = *(unsigned long long*)arg;
    double total = 0;

    for (unsigned long long i = 0; i < totalCount; ++i) {
        double x = randomNumberGenerator();
        double y = randomNumberGenerator();
        double result = sqrt(x * x + y * y);
        if (result <= 1) {
            total++;
        }
    }

    auto* resultPtr = new double(total);
    pthread_exit(resultPtr);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Input: " << argv[0] << " Total_Iteration" << endl;
        return 1;
    }

    seed = time(nullptr);

    unsigned long long totalCount = atoll(argv[1]);

    clock_t startTime = clock();

    pthread_t thread;
    void* threadResult;

    pthread_create(&thread, nullptr, calculatePi, (void*)&totalCount);
    pthread_join(thread, &threadResult);

    auto* totalPtr = (double*)threadResult;
    double total = *totalPtr;

    delete totalPtr;

    cout << "Value for Pi: " << 4 * (total / totalCount) << endl;

    clock_t endTime = clock();

    double totalTime = double (endTime - startTime) / CLOCKS_PER_SEC;

    cout << "Total time take for execution: " << totalTime << " seconds" << endl;

    return 0;
}
