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

    pthread_t thread;
    void* threadResult;

    pthread_create(&thread, nullptr, calculatePi, (void*)totCount);
    pthread_join(thread, &threadResult);

    auto* totalPtr = (float*)threadResult;
    float total = *totalPtr;

    delete totalPtr;

    cout << "Value for Pi: " << 4 * (total / totCount) << endl;

    return 0;
}
