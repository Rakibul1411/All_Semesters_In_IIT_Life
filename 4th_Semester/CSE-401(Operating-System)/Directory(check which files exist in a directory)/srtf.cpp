#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

struct ProcessObj {
    int id;
    int arrivalTime;
    int burstTime;
    int completeTime;
    int turnaroundTime;
    int waitingTime;
    string name;
};

class ShortestRemainingTime {
private:
    int time = 0;
    int timeQuantum = 1;
    vector<ProcessObj> q;
    vector<ProcessObj> list;
    vector<ProcessObj> completed;

public:
    void addToQueue() {
        if (!list.empty()) {
            for (int i = 0; i < list.size(); i++) {
                ProcessObj p = list[i];
                if (time >= p.arrivalTime) {
                    q.push_back(p);
                    list.erase(list.begin() + i);
                }
            }
        }
    }

    ProcessObj selectTheBest() {
        vector<int> bTimelist;
        if (!q.empty()) {
            for (int i = 0; i < q.size(); i++) {
                bTimelist.push_back(q[i].burstTime);
            }
            sort(bTimelist.begin(), bTimelist.end());

            for (int i = 0; i < q.size(); i++) {
                if (bTimelist[0] == q[i].burstTime) {
                    if (bTimelist[0] == 1) {
                        for (int j = 0; j < completed.size(); j++) {
                            if (q[i].id == completed[j].id) {
                                ProcessObj p = completed[j];
                                p.completeTime = time + 1;
                                completed[j] = p;
                            }
                        }
                        ProcessObj p = q[i];
                        q.erase(q.begin() + i);
                        return p;
                    } else {
                        ProcessObj p = q[i];
                        ProcessObj pNext = p;
                        pNext.burstTime = p.burstTime - 1;
                        q[i] = pNext;
                        return p;
                    }
                }
            }
        }
        return ProcessObj();
    }

    void simulateShortestRemainingTime(vector<ProcessObj>& l, vector<ProcessObj>& comp) {
        cout << "Started the shortest remaining time first algorithm--->" << endl;
        list.insert(list.end(), l.begin(), l.end());
        completed = comp;

        while (!list.empty() || !q.empty()) {
            addToQueue();

            while (q.empty()) {
                cout << "------Waiting to receive a process---------" << endl;
                sleep_for(seconds(1));
                time++;
                addToQueue();
            }

            ProcessObj processRun = selectTheBest();
            cout << "Process with name - " << processRun.name << " and Id = " << processRun.id << " is going to run" << endl;
            for (int j = 0; j < timeQuantum; j++) {
                cout << "------running a second--------" << endl;
                sleep_for(seconds(1));
                time++;
                addToQueue();
            }
        }

        for (int j = 0; j < completed.size(); j++) {
            ProcessObj& p = completed[j];
            p.burstTime = l[j].burstTime;
            p.turnaroundTime = p.completeTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            completed[j] = p;
        }

        for (int i = 0; i < completed.size(); i++) {
            cout << "Process Arrival time = " << completed[i].arrivalTime << endl;
            cout << "Process Completed time = " << completed[i].completeTime << endl;
            cout << "Process Turnaround time = " << completed[i].turnaroundTime << endl;
            cout << "Process Burst time = " << completed[i].burstTime << endl;
            cout << "Process Waiting time = " << completed[i].waitingTime << endl;
            cout << "---------------------------------------------------------" << endl;
        }
    }
};

int main() {
    ShortestRemainingTime srt;
    vector<ProcessObj> processes = {{1, 0, 10, 0, 0, 0, "P1"}, {2, 2, 4, 0, 0, 0, "P2"}, {3, 4, 8, 0, 0, 0, "P3"}};
    vector<ProcessObj> completed;
    srt.simulateShortestRemainingTime(processes, completed);
    return 0;
}
