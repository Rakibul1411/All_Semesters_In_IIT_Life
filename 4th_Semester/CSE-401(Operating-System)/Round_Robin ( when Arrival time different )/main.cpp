#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

struct Process {
    int pid;
    string processName;
    int arrivalTime = 0;
    int burstTime = 0;
    int burstTimeRemaining = 0;
    int completionTime = 0;
    int turnaroundTime = 0;
    int waitingTime = 0;
    bool isComplete;
    bool execute;
};

void checkForNewArrivals(vector<Process>& processes, int currentTime, queue<int>& readyQueue) {
    for (int i = 0; i < processes.size(); i++) {
        if (processes[i].arrivalTime <= currentTime && !processes[i].isComplete && !processes[i].execute) {
            readyQueue.push(i);
            processes[i].execute = true;
        }
    }
}

void roundRobin(vector<Process> &processes, int quantum,  vector<pair<string, int> >& store) {
    int n = processes.size();
    queue<int> readyQueue;
    int currentTime = 0;
    int totalExecuted = 0;
    int lastCompletionTime = 0;

    while (totalExecuted < n) {
        checkForNewArrivals(processes, currentTime, readyQueue);

        if (readyQueue.empty()) {
            currentTime++;
            continue;
        }

        int pid = readyQueue.front();
        readyQueue.pop();

        Process& currentProcess = processes[pid];

        if (currentTime > lastCompletionTime) {
            //int idleTime = currentTime - lastCompletionTime;
            store.push_back(make_pair("Idle", currentTime));
        }

        if (currentProcess.burstTimeRemaining <= quantum) {
            currentTime += currentProcess.burstTimeRemaining;
            currentProcess.completionTime = currentTime;
            store.push_back(make_pair(currentProcess.processName, currentTime));
            currentProcess.isComplete = true;
            currentProcess.execute = true;
            totalExecuted++;
        } else {
            currentTime += quantum;
            currentProcess.burstTimeRemaining -= quantum;
            store.push_back(make_pair(currentProcess.processName, currentTime));
            currentProcess.execute = true;
            checkForNewArrivals(processes, currentTime, readyQueue);
            if(currentProcess.burstTimeRemaining != 0){
                readyQueue.push(pid);
            }
        }

        lastCompletionTime = currentTime;
    }
}

bool customSort(const Process& a, const Process& b) {
    if (a.arrivalTime != b.arrivalTime) {
        return a.arrivalTime < b.arrivalTime;
    } else {
        return a.pid < b.pid;
    }
}

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> quantum;

    vector<Process> processes(n);

    freopen("input.txt", "r", stdin);
    for (int i = 0; i < n; i++) {
        cin >> processes[i].pid;
        cin >> processes[i].processName;
        cin >> processes[i].arrivalTime;
        cin >> processes[i].burstTime;
        processes[i].burstTimeRemaining = processes[i].burstTime;
    }

    //fclose(stdin);

//    for (int i = 0; i < n; i++) {
//        cout << "Enter details for Process " << i + 1 << ":" << endl;
//        cout << "PID: ";
//        cin >> processes[i].pid;
//        cout << "Process Name: ";
//        cin >> processes[i].processName;
//        cout << "Arrival Time: ";
//        cin >> processes[i].arrivalTime;
//        cout << "Burst Time: ";
//        cin >> processes[i].burstTime;
//        processes[i].burstTimeRemaining = processes[i].burstTime;
//    }

    sort(processes.begin(), processes.end(), customSort);

    vector<pair<string, int> > store;
    roundRobin(processes, quantum, store);

    cout << "Gantt Chart: " << endl;
    cout << "|    ";
    for (const auto& pair : store) {
        cout << pair.first << "    |    ";
    }
    cout << endl;

    int current = 0;
    cout << current << "         ";
    for (const auto& pair : store) {
        cout << pair.second << "         ";
    }
    cout << endl;

    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    cout << endl << endl;
    cout << "Waiting Time: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << processes[i].processName << " = " << processes[i].waitingTime << endl;
    }

    cout << endl << "Turn Around Time: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << processes[i].processName << " = " << processes[i].turnaroundTime << endl;
    }

    cout << endl << "Average Waiting Time: " << totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << totalTurnaroundTime / n << endl;

    return 0;
}
