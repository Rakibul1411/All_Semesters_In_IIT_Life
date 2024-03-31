#include <iostream>
#include <vector>
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
    int no_of_processes;
    cout << "Enter the number of process: ";
    cin >> no_of_processes;

    vector<Process> process(no_of_processes);

    freopen("input.txt", "r", stdin);
    for (int i = 0; i < no_of_processes; ++i) {
        cin >> process[i].name;
        cin >> process[i].burst_time;
    }

    struct Process temp;
    for (int i = 1; i < no_of_processes; ++i) {
        for (int j = i+1; j < no_of_processes; ++j) {
            if(process[i].burst_time > process[j].burst_time){
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    for (int i = 0; i < no_of_processes; ++i) {
        if(i == 0) {
            process[i].completion_time = process[i].burst_time;
        }
        else{
            process[i].completion_time = process[i-1].completion_time + process[i].burst_time;
        }

    }

    cout<<"Grant Chart:"<<endl;
    for (int i = 0; i < no_of_processes; ++i) {
        cout<<" | "<<process[i].name;
    }
    cout<<" |" << endl;

    for (int i = 0; i < no_of_processes; ++i) {
        if(i ==0) {
            cout <<" 0 "<<"   "<<process[i].completion_time;
            cout<<"  ";
        } else{
            cout<<"  "<<process[i].completion_time<<"  ";
        }
    }

    cout<<endl<<endl;
//    int previous_time=0;
//    for (int i = 0; i < no_of_processes; ++i) {
//        cout<<"Execution Time: ("<<previous_time<<","<<process[i].completion_time<<") --->"<<" Process: "<<process[i].name<<endl;
//        previous_time = process[i].completion_time;
//    }

    for (int i = 0; i < no_of_processes; ++i) {
        process[i].turn_around_time = (process[i].completion_time - process[i].arrival_time);
        process[i].waiting_time = (process[i].turn_around_time - process[i].burst_time);
    }

    cout<<endl<<"Turn Around Time: "<<endl;
    for (int i = 0; i < no_of_processes; ++i) {
        cout<<process[i].name<<" = "<<process[i].turn_around_time<<endl;
    }

    cout<<endl;
    cout<<"Waiting Time: "<<endl;
    for (int i = 0; i < no_of_processes; ++i) {
        cout<<process[i].name<<" = "<<process[i].waiting_time<<endl;
    }

    cout<<endl;
    double sum_turn_around_time=0;
    for (int i = 0; i < no_of_processes; ++i) {
        sum_turn_around_time += process[i].turn_around_time;
    }
    cout<<"Average TurnAround Time: "<<(sum_turn_around_time / no_of_processes)<<endl;

    double sum_waiting_time=0;
    for (int i = 0; i < no_of_processes; ++i) {
        sum_waiting_time += process[i].waiting_time;
    }
    cout<<"Average Waiting Time: "<<(sum_waiting_time / no_of_processes) <<endl;

    return 0;
}
