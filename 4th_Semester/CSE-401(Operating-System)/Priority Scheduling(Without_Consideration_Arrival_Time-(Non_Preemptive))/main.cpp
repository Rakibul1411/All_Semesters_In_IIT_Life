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
    int priority{};
};

bool compareProcessesByPriority(const Process &a, const Process &b) {
    return a.priority > b.priority;
}

int main() {
    int p;
    cout << "Enter the number of processes: ";
    cin >> p;

    vector<Process> process(p);

    freopen("input.txt", "r", stdin);

    for (int i = 0; i < p; ++i) {
        cin >> process[i].name;
        cin >> process[i].burst_time;
        cin>>process[i].priority;
    }

    sort(process.begin(), process.end(), compareProcessesByPriority);

    for (int i = 0; i < p; ++i) {
        if(i == 0) {
            process[i].completion_time = process[i].burst_time;
        }
        else{
            process[i].completion_time = process[i-1].completion_time + process[i].burst_time;
        }

    }
    cout<< endl;

    //Print the Gantt Chart
    cout<<"Grant Chart:"<<endl;
    cout << "Grant Chart:" << endl;
    cout << "|   ";
    for (int i = 0; i < p; ++i) {
        if(i == 0) {
            cout << process[i].name << "   |   ";
        }
        else{
            cout << process[i].name << "   |   ";
        }
    }

    cout << endl;

    for (int i = 0; i < p; ++i) {
        if(i == 0){
            cout << "0" << "        " << process[i].completion_time;
        } else{
            cout << "       " << process[i].completion_time;
        }
    }

    cout<<endl << endl;

    for (int i = 0; i < p; ++i) {
        process[i].turn_around_time=(process[i].completion_time-process[i].arrival_time);
        process[i].waiting_time = (process[i].completion_time-process[i].burst_time);
    }

    cout<<endl<<"Turn Around Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<process[i].name<<" = "<<process[i].turn_around_time<<endl;
    }

    cout<<endl;
    cout<<"Waiting Time: "<<endl;
    for (int i = 0; i < p; ++i) {
        cout<<process[i].name<<" = "<<process[i].waiting_time<<endl;
    }

    cout<<endl;
    double sum_turn_around_time=0;
    for (int i = 0; i < p; ++i) {
        sum_turn_around_time +=process[i].turn_around_time;
    }
    cout<<"Average TurnAround Time: "<<(sum_turn_around_time / p)<<endl;

    double sum_waiting_time=0;
    for (int i = 0; i < p; ++i) {
        sum_waiting_time +=process[i].waiting_time;
    }
    cout<<"Average Waiting Time: "<<(sum_waiting_time / p) << endl;

    return 0;
}
