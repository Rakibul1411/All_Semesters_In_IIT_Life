#include <iostream>
#include<vector>
#include <string>
using namespace std;

struct Process{
    string name;
    int arrival_time{};
    int burst_time{};
    int start_time=0;
    int completion_time{};
    int turn_around_time=0;
    int waiting_time=0;
    bool execute= false;
};
int main() {

    int p;
    cout<<"Enter the number of process: ";
    cin>> p;

    vector<Process> processes(p);

    freopen("input.txt", "r", stdin);
    for (int i = 0; i < p; ++i) {
        cin >>processes[i].name;
        cin>> processes[i].arrival_time;
        cin>>processes[i].burst_time;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    for (int i = 0; i < p; ++i) {
        if(i == 0){
            processes[i].completion_time = processes[i].burst_time;
            processes[i].execute = true;
        }
        else{
            if(processes[i-1].completion_time >= processes[i].arrival_time){
                for (int j = 0; j <= i; ++j) {
                    if(!processes[j].execute){
                        processes[j].completion_time = processes[j-1].completion_time + processes[j].burst_time;
                        processes[j].execute = true;
                        processes[j].start_time = processes[j-1].completion_time;
                    }
                }
            }
            else if(processes[i-1].completion_time < processes[i].arrival_time){
                processes[i].start_time = processes[i].arrival_time;
                processes[i].completion_time = processes[i].start_time + processes[i].burst_time;
                processes[i].execute = true;
            }
        }
    }
    cout<<endl;

    // Print Gantt Chart
    cout << "Grant Chart:" << endl;
    cout << "|   ";
    for (int i = 0; i < p; ++i) {
        if(i == 0) {
            cout << processes[i].name << "  |   ";
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
            cout << processes[i].start_time << "      " << processes[i].completion_time;
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

    cout<<endl<<"Turn around time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<processes[i].name<<" = "<<processes[i].turn_around_time<<endl;
        sum_turn_around_time += processes[i].turn_around_time;
    }

    cout<<endl<<"Waiting time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<processes[i].name<<" = "<<processes[i].waiting_time<<endl;
        sum_waiting_time += processes[i].waiting_time;
    }

    avg_turn_around_time = (sum_turn_around_time/p);
    avg_waiting_time = (sum_waiting_time/p);

    cout<<endl<<"Average Turn around time: "<<avg_turn_around_time <<endl;
    cout<<endl<<"Average Waiting time: "<< avg_waiting_time<<endl;

    return 0;
}
