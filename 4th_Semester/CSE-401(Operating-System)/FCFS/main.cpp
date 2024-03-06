#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int p=5;
struct Process {
    string name;
    int burst_time;
    int arrival_time=0;
    int completion_time=0;
    int turn_around_time=0;
    int waiting_time=0;
}process[p];

int main() {

    for (int i = 0; i < p; ++i) {
        cout<<"Input Process name: ";
        cin >> process[i].name;
        cout<<"Input Brust time: ";
        cin >> process[i].burst_time;
    }

    for (int i = 0; i < p; ++i) {
        if(i == 0) {
            process[i].completion_time = process[i].burst_time;
        }
        else{
            process[i].completion_time = process[i-1].completion_time + process[i].burst_time;
        }
    }

//    cout<<"Grant Chart:"<<endl;
//    for (int i = 0; i < p; ++i) {
//        cout<<" | "<<process[i].name;
//    }
//    cout<<" |" << endl;
//
//    for (int i = 0; i < p; ++i) {
//        if(i ==0) {
//            cout <<" 0 "<<"   "<<process[i].completion_time;
//            cout<<"  ";
//        } else{
//            cout<<"  "<<process[i].completion_time<<"  ";
//        }
//    }

    int previous_time=0;
    for (int i = 0; i < p; ++i) {
        cout<<"Execution Time: ("<<previous_time<<","<<process[i].completion_time<<") --->"<<" Process: "<<process[i].name<<endl;
        previous_time = process[i].completion_time;
    }


    for (int i = 0; i < p; ++i) {
        process[i].turn_around_time=(process[i].completion_time-process[i].arrival_time);
        process[i].waiting_time = (process[i].completion_time-process[i].burst_time);
    }

    cout<<endl<<"Turn Around Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<process[i].name<<"="<<process[i].turn_around_time<<endl;
    }

    cout<<"Waiting Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<process[i].name<<"="<<process[i].waiting_time<<endl;
    }

    double sum_turn_around_time=0;
    for (int i = 0; i < p; ++i) {
        sum_turn_around_time +=process[i].turn_around_time;
    }
    cout<<"Average TurnAround Time: "<<(sum_turn_around_time/p)<<endl;

    double sum_waiting_time=0;
    for (int i = 0; i < p; ++i) {
        sum_waiting_time +=process[i].waiting_time;
    }
    cout<<"Average Waiting Time: "<<(sum_waiting_time/p);

    return 0;
}
