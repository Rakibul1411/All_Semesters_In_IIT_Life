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

    Process processes[p];
    freopen("input.txt", "r", stdin);
    for (int i = 0; i < p; ++i) {
        cin >>processes[i].name;
        cin>> processes[i].arrival_time;
        cin>>processes[i].burst_time;
    }

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

    cout<<"Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<"Process name: "<<processes[i].name<<", start time: "<<processes[i].start_time<<", "<<"Completion time: "<<processes[i].completion_time<<endl;
    }

    cout<<endl;
    cout<<"Grant Chart: "<<endl;
    for (int i = 0; i < p; ++i) {
        if(i == 0){
            cout<<"Process: "<<processes[i].name<<", "<<"Execution time: "<<"("<<processes[i].start_time<<", "<<processes[i].completion_time<<")"<<endl;
        }
        else if(i == p-1){
            cout<<"Process: "<<processes[i].name<<", "<<"Execution time: "<<"("<<processes[i].start_time<<", "<<processes[i].completion_time<<")"<<endl;
        }
        else {
            if (processes[i-1].completion_time != processes[i].start_time) {
                cout << "Process: IDLE CASE<<, " << "Execution time: " << "(" << processes[i-1].completion_time << ", "
                     << processes[i].start_time << ")" << endl;
                cout << "Process: " << processes[i].name << ", " << "Execution time: " << "(" << processes[i].start_time
                     << ", " << processes[i].completion_time << ")" << endl;

            } else{
                cout << "Process: " << processes[i].name << ", " << "Execution time: " << "(" << processes[i].start_time
                     << ", " << processes[i].completion_time << ")" << endl;
            }
        }

    }

    for (int i = 0; i < p; ++i) {
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
    }

    double avg_turn_around_time, avg_waiting_time, sum_turn_around_time=0, sum_waiting_time=0;

    cout<<endl<<"Turn around time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<processes[i].name<<"= "<<processes[i].turn_around_time<<endl;
        sum_turn_around_time += processes[i].turn_around_time;
    }

    cout<<endl<<"Waiting time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<processes[i].name<<"= "<<processes[i].waiting_time<<endl;
        sum_waiting_time += processes[i].waiting_time;
    }

    avg_turn_around_time = (sum_turn_around_time/p);
    avg_waiting_time = (sum_waiting_time/p);

    cout<<endl<<"Average Turn around time: "<<avg_turn_around_time <<endl;
    cout<<endl<<"Average Waiting time: "<< avg_waiting_time<<endl;
    return 0;
}
