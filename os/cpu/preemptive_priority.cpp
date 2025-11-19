#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Process {
public:
    int id, arrival, burst, priority;
    int remaining, completion, turnaround, waiting, response;
    bool started;

    Process(int i=0, int a=0, int b=0, int p=0) {
        id = i; arrival = a; burst = b; priority = p;
        remaining = b; completion = turnaround = waiting = response = 0;
        started = false;
    }
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i=0; i<n; i++) {
        int id, at, bt, pr;
        cout << "Enter Process ID, Arrival Time, Burst Time, Priority: ";
        cin >> id >> at >> bt >> pr;
        processes[i] = Process(id, at, bt, pr);
    }

    int time = 0, completed = 0;
    vector<int> gantt;
    while (completed < n) {
        int idx = -1, highPr = 1e9;
        for (int i=0; i<n; i++) {
            if (processes[i].arrival <= time && processes[i].remaining > 0) {
                if (processes[i].priority < highPr) {
                    highPr = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            gantt.push_back(processes[idx].id);
            if (!processes[idx].started) {
                processes[idx].response = time - processes[idx].arrival;
                processes[idx].started = true;
            }
            processes[idx].remaining--;
            time++;

            if (processes[idx].remaining == 0) {
                processes[idx].completion = time;
                processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
                processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
                completed++;
            }
        } else {
            time++;
        }
    }

    cout << "\nProcess Table:\n";
    cout << "ID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n";
    for (auto &p : processes) {
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" << p.priority
             << "\t" << p.completion << "\t" << p.turnaround
             << "\t" << p.waiting << "\t" << p.response << "\n";
    }

    cout << "\nGantt Chart:\n| ";
    for (int id : gantt) cout << "P" << id << " | ";
    cout << "\n";

    return 0;
}
