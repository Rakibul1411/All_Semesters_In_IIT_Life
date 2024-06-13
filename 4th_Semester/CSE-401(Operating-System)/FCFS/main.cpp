#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Process {
    string name;
    int burst_time{};
    int arrival_time=0;
    int completion_time=0;
    int turn_around_time=0;
    int waiting_time=0;
};

int main() {
    int p;
    cout<<"Enter the number of process: ";
    cin>> p;

    vector<Process> processes(p);

    freopen("input.txt", "r", stdin);
    for (auto & process : processes) {
        cin >> process.name;
        cin >> process.burst_time;
    }

    for (int i = 0; i < p; ++i) {
        if(i == 0) {
            processes[i].completion_time = processes[i].burst_time;
        }
        else{
            processes[i].completion_time = processes[i-1].completion_time + processes[i].burst_time;
        }
    }

    cout<<"Grant Chart:"<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<" | "<<processes[i].name;
    }
    cout<<" |" << endl;

    for (int i = 0; i < p; ++i) {
        if(i ==0) {
            cout <<" 0 "<<"   "<<processes[i].completion_time;
            cout<<"  ";
        } else{
            cout<<"  "<<processes[i].completion_time<<"  ";
        }
    }

//    cout<<"Gantt Chart: "<<endl;
//    int previous_time=0;
//    for (int i = 0; i < p; ++i) {
//        cout<<"Execution Time: ("<<previous_time<<","<<processes[i].completion_time<<") --->"<<" Process: "<<processes[i].name<<endl;
//        previous_time = processes[i].completion_time;
//    }


    for (int i = 0; i < p; ++i) {
        processes[i].turn_around_time = (processes[i].completion_time - processes[i].arrival_time);
        processes[i].waiting_time = (processes[i].completion_time - processes[i].burst_time);
    }

    cout<<endl<<endl;
    cout << "Completion Time: "<<endl;
    for (auto & process: processes) {
        cout<<process.name << " = " << process.completion_time << endl;
    }

    cout<<endl<<"Turn Around Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<processes[i].name<<" = "<<processes[i].turn_around_time<<endl;
    }

    cout<<endl<<"Waiting Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<processes[i].name<<" = "<<processes[i].waiting_time<<endl;
    }

    cout<< endl;

    double sum_turn_around_time=0;
    for (int i = 0; i < p; ++i) {
        sum_turn_around_time += processes[i].turn_around_time;
    }
    cout<<"Average TurnAround Time: "<<(sum_turn_around_time / p)<<endl;

    double sum_waiting_time=0;
    for (int i = 0; i < p; ++i) {
        sum_waiting_time += processes[i].waiting_time;
    }
    cout<<"Average Waiting Time: "<<(sum_waiting_time / p);

    return 0;
}
