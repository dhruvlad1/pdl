#include <iostream>
#include <vector>
using namespace std;

class SJF {
public:
    int process_id, arrival_time, burst_time;
    int completion_time, waiting_time, turnaround_time;
    bool is_completed;

    SJF(int id=0, int arr=0, int bt=0) {
        process_id = id;
        arrival_time = arr;
        burst_time = bt;
        completion_time = 0;
        waiting_time = 0;
        turnaround_time = 0;
        is_completed = false;
    }

    void printtable(vector<SJF>& v) {
        cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
        for (auto &p : v) {
            cout << p.process_id << "\t\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t"
                 << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << endl;
        }
    }
};

class SJF_Calculation {
public:
    void calculate(vector<SJF>& processes, vector<pair<int,int>>& gantt_ids, vector<pair<int,int>>& gantt_times) {
        int n = processes.size();
        int completed = 0;
        int time = 0;

        while (completed < n) {
            int idx = -1;
            int min_bt = INT32_MAX;

            for (int i=0; i<n; i++) {
                if (!processes[i].is_completed && processes[i].arrival_time <= time) {
                    if (processes[i].burst_time < min_bt) {
                        min_bt = processes[i].burst_time;
                        idx = i;
                    }
                    else if (processes[i].burst_time == min_bt) {
                        if (processes[i].arrival_time < processes[idx].arrival_time) {
                            idx = i;
                        }
                    }
                }
            }

            if (idx != -1) {
                int start_time = time;
                time += processes[idx].burst_time;

                processes[idx].completion_time = time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                processes[idx].is_completed = true;

                gantt_ids.push_back({processes[idx].process_id, idx});
                gantt_times.push_back({start_time, time});
                completed++;
            } else {
                time++;
            }
        }
    }
};

int main() {
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<SJF> processes(n);
    for (int i=0; i<n; i++) {
        int id, arr, bt;
        cout<<"Enter details for Process " << i+1 << ":\n";
        cout<<"Process ID: ";
        cin>>id;
        cout<<"Arrival Time: ";
        cin>>arr;
        cout<<"Burst Time: ";
        cin>>bt;
        processes[i] = SJF(id, arr, bt);
    }

    vector<pair<int,int>> gantt_ids;
    vector<pair<int,int>> gantt_times;

    SJF_Calculation sjf;
    sjf.calculate(processes, gantt_ids, gantt_times);

    cout << "\nFinal Process Table:\n";
    processes[0].printtable(processes);

    cout << "\nGantt Chart:\n";
    for (int i=0; i<gantt_ids.size(); i++) {
        cout << "| P" << gantt_ids[i].first << " ";
    }

    cout << "|\n";

    cout << gantt_times[0].first;
    for (int i=0; i<gantt_times.size(); i++) {
        cout << "    " << gantt_times[i].second;
    }
    cout << endl;

    return 0;
}
