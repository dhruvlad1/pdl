#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

class SRTF {
private:
    vector<Process> processes;
    vector<int> gantt_pid;
    int n;

public:
    void input() {
        cout << "Enter number of processes: ";
        cin >> n;
        processes.resize(n);
        for (int i = 0; i < n; i++) {
            cout << "Enter details for Process " << i + 1 << ":\n";
            cout << "Process ID: ";
            cin >> processes[i].pid;
            cout << "Arrival Time: ";
            cin >> processes[i].arrival_time;
            cout << "Burst Time: ";
            cin >> processes[i].burst_time;
            processes[i].remaining_time = processes[i].burst_time;
        }
    }

    void calculate() {
        int completed = 0, current_time = 0;

        while (completed != n) {
            int idx = -1;
            int min_remaining = 1e9;

            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                    if (processes[i].remaining_time < min_remaining) {
                        min_remaining = processes[i].remaining_time;
                        idx = i;
                    }
                    if (processes[i].remaining_time == min_remaining) {
                        if (processes[i].arrival_time < processes[idx].arrival_time)
                            idx = i;
                    }
                }
            }

            if (idx != -1) {
                gantt_pid.push_back(processes[idx].pid);
                processes[idx].remaining_time--;
                current_time++;

                if (processes[idx].remaining_time == 0) {
                    processes[idx].completion_time = current_time;
                    processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                    processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                    completed++;
                }
            } else {
                gantt_pid.push_back(-1); // CPU idle
                current_time++;
            }
        }
    }

    void displayTable() {
        cout << "\nFinal Process Table:\n";
        cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
        for (auto &p : processes) {
            cout << p.pid << "\t\t"
                 << p.arrival_time << "\t\t"
                 << p.burst_time << "\t\t"
                 << p.completion_time << "\t\t"
                 << p.turnaround_time << "\t\t"
                 << p.waiting_time << "\n";
        }
    }

    void displayGanttChart() {
        cout << "\nGantt Chart:\n|";
        for (int i = 0; i < gantt_pid.size(); i++) {
            if (i == 0 || gantt_pid[i] != gantt_pid[i - 1]) {
                if (i != 0 && gantt_pid[i - 1] != -1) cout << " P" << gantt_pid[i - 1] << " |";
            }
            if (i == gantt_pid.size() - 1 && gantt_pid[i] != -1) cout << " P" << gantt_pid[i] << " |";
        }

        cout << "\n0    ";
        for (int i = 1; i <= gantt_pid.size(); i++) {
            if (i == gantt_pid.size() || gantt_pid[i] != gantt_pid[i - 1]) cout << i << "    ";
        }
        cout << "\n";
    }

    void displayAverages() {
        double total_tat = 0, total_wt = 0;
        for (auto &p : processes) {
            total_tat += p.turnaround_time;
            total_wt += p.waiting_time;
        }
        cout << "\nAverage Turnaround Time = " << total_tat / n;
        cout << "\nAverage Waiting Time = " << total_wt / n << "\n";
    }
};

int main() {
    SRTF s;
    s.input();
    s.calculate();
    s.displayTable();
    s.displayGanttChart();
    s.displayAverages();
    return 0;
}
