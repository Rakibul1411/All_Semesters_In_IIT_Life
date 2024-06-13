#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

using namespace std;
unsigned int seed;

double randomNumberGenerator() {
    return rand_r(&seed) / (double)RAND_MAX;
}

void* calculatePi(void* arg) {
    auto totalCount = *(unsigned long long*)arg;
    unsigned long long insideCircleCount = 0;

    for (unsigned long long i = 0; i < totalCount; ++i) {
        double x = randomNumberGenerator();
        double y = randomNumberGenerator();
        double distance = x * x + y * y;
        if (distance <= 1) {
            insideCircleCount++;
        }
    }

    auto* resultPtr = new double((double)insideCircleCount / totalCount);
    pthread_exit(resultPtr);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Please Input Correct format in command line." << endl;
        return 1;
    }

    seed = time(nullptr);

    unsigned long long totalCount = atoll(argv[1]);
    unsigned long long totalCountPerThread = totalCount / 10;

    clock_t startTime = clock();

    pthread_t threads[10];
    double* threadResults[10];

    for (int i = 0; i < 10; ++i) {
        pthread_create(&threads[i], nullptr, calculatePi, (void*)&totalCountPerThread);
    }

    for (int i = 0; i < 10; ++i) {
        pthread_join(threads[i], (void**)&threadResults[i]);
    }

    double totalInsideCircleRatio = 0;
    for (int i = 0; i < 10; ++i) {
        totalInsideCircleRatio += *threadResults[i];
        delete threadResults[i];
    }


    double estimatedPi = 4.0 * totalInsideCircleRatio / 10;
    cout << "Estimated value of Pi: " << estimatedPi << endl;

    clock_t endTime = clock();

    double totalTime = double (endTime - startTime) / CLOCKS_PER_SEC;

    cout << "Total time take for execution: " << totalTime << " seconds" << endl;

    return 0;
}
