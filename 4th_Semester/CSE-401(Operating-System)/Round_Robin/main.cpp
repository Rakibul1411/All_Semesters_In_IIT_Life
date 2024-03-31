#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Process {
    string name;
    int burst_time = 0;
    int arrival_time = 0;
    int completion_time = 0;
    int turn_around_time = 0;
    int waiting_time = 0;
};

int main() {
    int p;
    cout<<"Enter the number of processes: ";
    cin>> p;

    vector<Process> processes(p);
    vector<Process> store(p);
    map<int, string> myMap;

    int time_quantum;

    cout << "Enter the time quantum: ";
    cin >> time_quantum;

    freopen("input.txt", "r", stdin);
    for (int i = 0; i < p; ++i) {
        cin >> processes[i].name;
        cin >> processes[i].burst_time;
    }

    store = processes;

    int current_time = 0;
    int remaining_processes = p;

    while (remaining_processes > 0) {
        for (int i = 0; i < p; ++i) {
            if (processes[i].burst_time > 0) {
                if (processes[i].arrival_time <= current_time) {
                    int execution_time = min(time_quantum, processes[i].burst_time);
                    current_time += execution_time;
                    processes[i].burst_time -= execution_time;
                    processes[i].completion_time = current_time;
                    //completion_times[i] = current_time;
                    myMap.insert({current_time, processes[i].name});

                    if (processes[i].burst_time == 0) {
                        for (int j = 0; j < p; ++j) {
                            if (processes[i].name == processes[j].name) {
                                processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
                                processes[i].waiting_time = processes[i].turn_around_time - store[i].burst_time;
                                --remaining_processes;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << endl;

    cout << "Gantt Chart: "<< endl;
    int previous_time = 0;
    cout << "|   ";
    for (auto & i : myMap) {
        cout << i.second << "   |   ";
    }
    cout << endl;
    cout << previous_time << "        ";
    for (auto & i : myMap) {
        cout << i.first << "        ";
    }

    double total_turnaround_time = 0, total_waiting_time = 0;
    for (int i = 0; i < p; ++i) {
        total_turnaround_time += processes[i].turn_around_time;
        total_waiting_time += processes[i].waiting_time;
    }

    for (int i = 0; i < p; ++i) {
        processes[i].turn_around_time = processes[i].completion_time-processes[i].arrival_time;
    }

    cout<<endl<<endl;

    cout<<"Turn Around Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<store[i].name<<" = "<<processes[i].completion_time-processes[i].arrival_time<<endl;
    }

    cout<<endl;

    cout<<"Waiting Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<store[i].name<<" = "<<processes[i].turn_around_time-store[i].burst_time<<endl;
    }

    cout<<endl;

    cout << "Average Turnaround Time: " << (total_turnaround_time / p) << endl;
    cout << "Average Waiting Time: " << (total_waiting_time / p) << endl;

    cout<<endl;


    return 0;
}
