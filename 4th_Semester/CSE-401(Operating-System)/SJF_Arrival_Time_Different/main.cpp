#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Process {
    string name;
    int burst_time{};
    int arrival_time{};
    int start_time = 0;
    int completion_time{};
    int turn_around_time{};
    int waiting_time{};
    bool execute = false;
};

int main() {
    int p;
    cout << "Enter the number of processes: ";
    cin >> p;

    vector<Process> processes(p);

    freopen("input.txt", "r", stdin);
    for (int i = 0; i < p; ++i) {
        cin >> processes[i].name;
        cin >> processes[i].arrival_time;
        cin >> processes[i].burst_time;
    }

//    struct Process temp;
//    for (int i = 0; i < p; ++i) {
//        for (int j = i+1; j < p; ++j) {
//            if(processes[j].arrival_time < processes[i].arrival_time){
//                temp = processes[i];
//                processes[i] = processes[j];
//                processes[j] = temp;
//            }
//        }
//    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0;

    for (int i = 0; i < p; ++i) {
        int shortest_job_index = -1;
        int shortest_burst_time = INT_MAX;
        for (int j = 0; j < p; ++j) {
            if (!processes[j].execute && processes[j].arrival_time <= current_time && processes[j].burst_time < shortest_burst_time) {
                shortest_job_index = j;
                shortest_burst_time = processes[j].burst_time;
            }
        }
        if (shortest_job_index != -1) {
            processes[shortest_job_index].start_time = current_time;
            processes[shortest_job_index].completion_time = current_time + processes[shortest_job_index].burst_time;
            processes[shortest_job_index].execute = true;
            current_time = processes[shortest_job_index].completion_time;
        } else {
            int next_process_index = -1;
            int min_arrival_time = INT_MAX;
            for (int j = 0; j < p; ++j) {
                if (!processes[j].execute && processes[j].arrival_time < min_arrival_time) {
                    next_process_index = j;
                    min_arrival_time = processes[j].arrival_time;
                }
            }
            current_time = min_arrival_time;
            processes[next_process_index].start_time = current_time;
            processes[next_process_index].completion_time = current_time + processes[next_process_index].burst_time;
            processes[next_process_index].execute = true;
            current_time = processes[next_process_index].completion_time;
        }
    }

    cout<<endl;

    // Print Gantt Chart
    cout << "Grant Chart:" << endl;
    cout << "|   ";
    for (int i = 0; i < p; ++i) {
        if(i == 0) {
            cout << processes[i].name << "   |   ";
        }
        else{
            if(processes[i-1].completion_time != processes[i].start_time){
                cout << "Idle  |   " << processes[i].name << "   |   ";
            }
            else{
                cout << processes[i].name << "   |   ";
            }
        }
    }
    cout << endl;

    for (int i = 0; i < p; ++i) {
        if(i == 0){
            cout << processes[i].start_time << "       " << processes[i].completion_time;
        } else{
            if(processes[i-1].completion_time != processes[i].start_time){
                cout << "         " << processes[i].start_time << "      " << processes[i].completion_time;
            } else{
                cout << "       " << processes[i].completion_time;
            }
        }
    }

    cout<<endl << endl;

    for (int i = 0; i < p; ++i) {
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
    }

    double avg_turn_around_time, avg_waiting_time, sum_turn_around_time=0, sum_waiting_time=0;

    cout<<"Turn Around Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<processes[i].name<<" = "<<processes[i].turn_around_time<<endl;
        sum_turn_around_time += processes[i].turn_around_time;
    }

    cout<<endl;
    cout<<"Waiting Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<processes[i].name<<" = "<<processes[i].waiting_time<<endl;
        sum_waiting_time += processes[i].waiting_time;
    }

    avg_turn_around_time = (sum_turn_around_time/p);
    avg_waiting_time = (sum_waiting_time/p);

    cout<<endl;
    cout<<"Average Turn Around time: "<<avg_turn_around_time<<endl;
    cout<<"Average Waiting time: "<<avg_waiting_time<<endl;
    return 0;
}
