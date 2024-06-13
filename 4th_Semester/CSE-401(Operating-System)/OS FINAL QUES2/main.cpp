#include<iostream>
#include <vector>
using namespace std;

int main(){
    freopen("input.txt", "r", stdin);
    int numberOfProcess, numberOfResource;
    cin >> numberOfProcess >> numberOfResource;

    vector<vector<int>> allocation, MaxNeeded, need;

    allocation.resize(numberOfProcess, vector<int>(numberOfResource));

    MaxNeeded.resize(numberOfProcess, vector<int>(numberOfResource));

    need.resize(numberOfProcess, vector<int>(numberOfResource));

    vector<int> availableResource(numberOfResource);

    for(int i = 0; i < numberOfProcess; i++){
        for(int j = 0; j < numberOfResource; j++){
            cin >> allocation[i][j];
        }
    }

    for(int i = 0; i < numberOfProcess; i++){
        for(int j = 0; j < numberOfResource; j++){
            cin >> MaxNeeded[i][j];
        }
    }

    for(int i = 0; i < numberOfResource; i++){
        cin >> availableResource[i];
    }

    for(int i = 0; i < numberOfProcess; i++){
        for(int j = 0; j < numberOfResource; j++){
            need[i][j] = MaxNeeded[i][j] - allocation[i][j];
        }
    }

    vector<int> work(numberOfResource);
    work = availableResource;

    vector<bool> finish(numberOfProcess, false);
    int initialNumberOfFinish = 0, numberOfFinish = 0;
    vector<string> ProcessCompletionOrder;

    while(true){
        for(int i = 0; i < numberOfProcess; i++){
            if(!finish[i]){
                bool isPossible = true;
                for(int j = 0; j < numberOfResource; j++){
                    if(need[i][j] > work[j]){
                        isPossible = false;
                        break;
                    }
                }
                if(isPossible){
                    for(int j = 0; j < numberOfResource; j++){
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    numberOfFinish++;
                    ProcessCompletionOrder.push_back("P" + to_string(i));
                }
            }
        }
        if(initialNumberOfFinish == numberOfFinish) break;
        else initialNumberOfFinish = numberOfFinish;
    }

    bool isSafe = true;
    bool check = false;
    for(auto fin : finish){
        if(!fin){
            cout << "System will turn into unsafe state." << endl;
            isSafe = false;
            check = true;
            break;
        }
    }

    if(check) {
        cout << "Unsafe State After Execution of Process: ";
        for (int i=0; i < ProcessCompletionOrder.size(); i++) {
            cout << ProcessCompletionOrder[i] << " ";
        }
    }

    if(isSafe){
        cout << "\nSystem will be safe state." << endl;
        cout << "Allocation order of Processes is: ";
        for(auto o: ProcessCompletionOrder){
            cout << o << " ";
        }
        cout << endl << endl;
    }

    return 0;
}