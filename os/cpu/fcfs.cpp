#include <iostream>
#include <vector>
using namespace std;

class FCFS {
public:
    int process_id, arrival_time, burst_time;
    int completion_time, waiting_time, turnaround_time;

    FCFS(int id=0, int arr=0, int bt=0) {
        process_id = id;
        arrival_time = arr;
        burst_time = bt;
        completion_time = 0;
        waiting_time = 0;
        turnaround_time = 0;
    }

    void printTable(vector<FCFS>& v) {
        cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
        for (auto &p : v) {
            cout << p.process_id << "\t\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t"
                 << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << endl;
        }
    }
};
// 1 0 5
// 2 7 3
class FCFS_Calculation {
public:
    void sortByArrival(vector<FCFS>& processes) {
        for (int i=0; i<processes.size(); i++) {
            for (int j=i+1; j<processes.size(); j++) {
                if (processes[i].arrival_time > processes[j].arrival_time) {
                    swap(processes[i], processes[j]);
                }
            }
        }
    }

    void calculate(vector<FCFS>& processes, vector<pair<int,int>>& gantt_ids, vector<pair<int,int>>& gantt_times) {
        sortByArrival(processes);
        int time = 0;

        for (int i=0; i<processes.size(); i++) {
            FCFS& p = processes[i];

            if (time < p.arrival_time) {
                time = p.arrival_time;  // CPU idle till process arrives
            }

            int start_time = time;
            time += p.burst_time;
            p.completion_time = time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;

            gantt_ids.push_back({p.process_id, i});
            gantt_times.push_back({start_time, time});
        }
    }
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<FCFS> processes(n);
    for (int i=0; i<n; i++) {
        int id, arr, bt;
        cout << "Enter details for Process " << i+1 << ":\n";
        cout << "Process ID: ";
        cin >> id;
        cout << "Arrival Time: ";
        cin >> arr;
        cout << "Burst Time: ";
        cin >> bt;
        processes[i] = FCFS(id, arr, bt);
    }

    vector<pair<int,int>> gantt_ids;
    vector<pair<int,int>> gantt_times;

    FCFS_Calculation fcfs;
    fcfs.calculate(processes, gantt_ids, gantt_times);

    cout << "\nFinal Process Table:\n";
    processes[0].printTable(processes);

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
