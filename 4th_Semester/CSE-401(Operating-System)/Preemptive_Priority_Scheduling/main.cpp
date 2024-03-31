#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;

struct Process {
    string name;
    int burst_time{};
    int arrival_time{};
    int priority{};
    int remaining_time{};
    int start_time = 0;
    int completion_time{};
    int turn_around_time{};
    int waiting_time{};
    bool execute = false;
    bool first_execute = false;
    bool count = true;
};

int main() {
    int p;
    cout << "Enter the number of processes: ";
    cin >> p;

    vector<Process> processes(p);
    vector<int> time_execute;
    vector<string> processes_name;

    freopen("input.txt", "r", stdin);
    for (int i = 0; i < p; ++i) {
        cin >> processes[i].name;
        cin >> processes[i].arrival_time;
        cin >> processes[i].burst_time;
        cin >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    bool temp = false;

    int current_time = 0;
    int completed_processes = 0;
    while (completed_processes < p) {
        int highest_priority_job_index = -1;
        int highest_priority = INT_MIN;

        for (int j = 0; j < p; ++j) {
            if (!processes[j].execute && processes[j].arrival_time <= current_time && processes[j].priority > highest_priority) {
                highest_priority_job_index = j;
                highest_priority = processes[j].priority;
                if(processes[highest_priority_job_index].count){
                    processes[highest_priority_job_index].first_execute = true;
                }
            }
        }

        if (highest_priority_job_index != -1) {

//            if(temp){
//                cout<<"IDLE Time: "<<current_time<<endl;
//                time_execute.push_back(current_time);
//                processes_name.emplace_back("Idle");
//                temp = false;
//            }

            if(processes[highest_priority_job_index].first_execute ) {
                processes[highest_priority_job_index].start_time = current_time;
                processes[highest_priority_job_index].count = false;
                processes[highest_priority_job_index].first_execute = false;
            }

            processes[highest_priority_job_index].completion_time = current_time + 1;
            processes[highest_priority_job_index].remaining_time -= 1;
            time_execute.push_back(processes[highest_priority_job_index].completion_time);
            processes_name.push_back(processes[highest_priority_job_index].name);

//            cout << "Process: " << processes[highest_priority_job_index].name << ", ";
//            cout << "Execution time: (" << current_time << ", " << processes[highest_priority_job_index].completion_time << ")" << endl;
            if (processes[highest_priority_job_index].remaining_time == 0) {
                processes[highest_priority_job_index].execute = true;
//                processes[highest_priority_job_index].turn_around_time = current_time + 1 - processes[highest_priority_job_index].arrival_time;
//                processes[highest_priority_job_index].waiting_time = processes[highest_priority_job_index].turn_around_time - processes[highest_priority_job_index].burst_time;
                completed_processes++;
            }
            current_time++;
        }
        else {
            current_time++;
            //cout<<"IDLE Time: "<<current_time<<endl;
            time_execute.push_back(current_time);
            processes_name.emplace_back("Idle");
            //temp = true;
        }
    }

    cout<<endl;
    for (int i = 0; i < p; ++i) {
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
//        cout << "Process name: " << processes[i].name << ", Start Time: " << processes[i].start_time << ", Completion Time: " << processes[i].completion_time << endl;
    }

    vector<pair<string, int>> print;
    int count = 0;
    string s = processes_name[0];

    for (int i = 0; i < time_execute.size(); ++i) {
        if (s == processes_name[i]) {
            count++;
        } else {
            print.emplace_back(s, count);
            s = processes_name[i];
            count = 1;
        }
    }
    print.emplace_back(s, count);

    //Print Gantt Chart
    cout << "Grant Chart: " << endl;
    cout << "|   ";
    for (const auto& p : print) {
        cout << p.first << "   |   ";
    }
    cout << endl << "0" << "       " ;
    int add = 0;
    for (const auto& p : print) {
        add += p.second;
        cout << add << "        " ;
    }

    cout << endl <<endl;

    double avg_turn_around_time=0, avg_waiting_time=0, sum_turn_around_time=0, sum_waiting_time=0;

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

    cout<< endl;

    for (int i = 0; i < p; ++i) {
        avg_turn_around_time += processes[i].turn_around_time;
        avg_waiting_time += processes[i].waiting_time;
    }

    avg_turn_around_time /= p;
    avg_waiting_time /= p;

    cout << "Average Turn Around time: " << avg_turn_around_time << endl;
    cout << "Average Waiting time: " << avg_waiting_time << endl;


    return 0;
}
