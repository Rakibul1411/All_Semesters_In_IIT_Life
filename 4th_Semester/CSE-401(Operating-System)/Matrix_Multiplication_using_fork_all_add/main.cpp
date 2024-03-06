#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    srand(time(NULL));
    int row, column, pid;
    do {
        cout << "Input: ";
        cin >> row >> column;
    } while (row < 0 || column < 0);

    int** matrixA = new int*[row];
    for (int i = 0; i < row; ++i) {
        matrixA[i] = new int[column];
    }

    int** matrixB = new int*[column];
    for (int i = 0; i < column; ++i) {
        matrixB[i] = new int[row];
    }

    int** matrixC = new int*[row];
    for (int i = 0; i < row; ++i) {
        matrixC[i] = new int[row];
    }

    for (int k = 0; k < row; k++) {
        for (int j = 0; j < column; j++) {
            matrixA[k][j] = rand() % 10 + 2;
            cout << matrixA[k][j] << " ";
        }
        cout << endl;
    }

    for (int k = 0; k < column; k++) {
        for (int j = 0; j < row; j++) {
            matrixB[k][j] = rand() % 10 + 2;
            cout << matrixB[k][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < row; i++) {
        cout << endl;
        for (int j = 0; j < row; j++) {
            pid = fork();
            if (pid == -1) {
                perror("Fork Fail");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                matrixC[i][j] = 0;
                for (int k = 0; k < column; k++) {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
                cout << "pid= " << getpid() << endl;
                cout << matrixC[i][j] << endl;
                exit(EXIT_SUCCESS);
            }
        }
    }


    for (int i = 0; i < row; i++) {
        wait(nullptr);
    }

    return 0;
}
