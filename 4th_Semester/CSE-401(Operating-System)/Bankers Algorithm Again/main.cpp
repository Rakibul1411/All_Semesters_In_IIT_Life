#include<iostream>
#include <vector>
using namespace std;

int main(){
    freopen("input.txt", "r", stdin);
    int numProcess, numResource;
    cin >> numProcess >> numResource;
    vector<vector<int>> allocation, maxx, need;
    allocation.resize(numProcess, vector<int>(numResource));
    maxx.resize(numProcess, vector<int>(numResource));
    need.resize(numProcess, vector<int>(numResource));
    vector<int> available(numResource);
    for(int i = 0; i < numProcess; i++){
        for(int j = 0; j < numResource; j++){
            cin >> allocation[i][j];
        }
    }
    for(int i = 0; i < numProcess; i++){
        for(int j = 0; j < numResource; j++){
            cin >> maxx[i][j];
        }
    }
    for(int i = 0; i < numResource; i++){
        cin >> available[i];
    }
    for(int i = 0; i < numProcess; i++){
        for(int j = 0; j < numResource; j++){
            need[i][j] = maxx[i][j] - allocation[i][j];
        }
    }
    vector<int> work(numResource);
    work = available;
    vector<bool> finish(numProcess, false);
    int initNumFinish = 0, numFinish = 0;
    vector<string> order;
    while(true){
        for(int i = 0; i < numProcess; i++){
            if(!finish[i]){
                bool isPossible = true;
                for(int j = 0; j < numResource; j++){
                    if(need[i][j] > work[j]){
                        isPossible = false;
                        break;
                    }
                }
                if(isPossible){
                    for(int j = 0; j < numResource; j++){
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    numFinish++;
                    order.push_back("P" + to_string(i));
                }
            }
        }
        if(initNumFinish == numFinish) break;
        else initNumFinish = numFinish;
    }
    bool isSafe = true;
    for(auto fin : finish){
        if(!fin){
            cout << "System is unsafe" << endl;
            isSafe = false;
            break;
        }
    }
    if(isSafe){
        cout << "System is safe" << endl;
        cout << "Allocation order is: ";
        for(auto o: order){
            cout << o << " ";
        }
        cout << endl << endl;
    }
}