#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <pthread.h>

using namespace std;

unsigned int seed;

float randomNumberGenerator() {
    return rand_r(&seed) / (float)RAND_MAX;
}

void* calculatePi(void* arg) {
    auto totCount = (long long)arg;
    float total = 0;

    for (long long i = 0; i < totCount; ++i) {
        float x = randomNumberGenerator();
        float y = randomNumberGenerator();
        float result = sqrt(x * x + y * y);
        if (result <= 1) {
            total += 1;
        }
    }

    auto* resultPtr = new float(total);
    pthread_exit(resultPtr);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <TOT_COUNT>" << endl;
        return 1;
    }

    seed = time(nullptr);

    unsigned long long totCount = atoll(argv[1]);
    unsigned long long totalCountPerThread = totCount / 10;

    pthread_t threads[10];
    void* threadResults[10];

    for (auto & thread : threads) {
        pthread_create(&thread, nullptr, calculatePi, (void*)totalCountPerThread);
    }

    float total = 0;
    for (int i = 0; i < 10; ++i) {
        pthread_join(threads[i], &threadResults[i]);
        total += *(float*)threadResults[i];
        delete (float*)threadResults[i];
    }

    cout << "Value for Pi: " << 4 * (total / totCount) << endl;

    return 0;
}
