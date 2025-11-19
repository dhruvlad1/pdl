#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class roundrobin {
public:
    int process_id, arrival_time, burst_time;
    int remaining_time, completiontime, waiting_time, turnaround_time, time_quantum;

    roundrobin(int id=0 , int arr=0, int bt =0) {
        process_id=id;
        arrival_time=arr;
        burst_time=bt;
        remaining_time=bt;
        completiontime=0;
        waiting_time=0;
        turnaround_time=0;
        time_quantum=0;
    }
    void rrtimequanta(int time) {
        time_quantum = time;
    }

    void printrr(vector<roundrobin>& v) {
        cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
        for (auto& p : v) {
            cout <<p.process_id<<"\t\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t"
                 <<p.completiontime<<"\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << endl;
        }
    }
};
class rrcalculation {
public:
    void sortbyarrival(vector <roundrobin>& processes) {
        for(int i=0; i<processes.size(); i++) {
            for(int j=i+1; j<processes.size(); j++) {
                if(processes[i].arrival_time > processes[j].arrival_time) {
                    swap(processes[i], processes[j]);
                }
            }
        }
    }
    void queuecalculation(vector<roundrobin>& processes, int time_quantum, vector<pair<int,int>>& gantt_ids, vector<pair<int,int>>& gantt_times) {
        int time = 0;
        queue<int> q;
        vector<bool> inqueue(processes.size(), false);
        int completed = 0;
        int n = processes.size();
        sortbyarrival(processes);
        q.push(0);
        inqueue[0] = true;

        while (completed < n) {
            if (q.empty()) {
                for (int i = 0; i < n; i++) {
                    if (!inqueue[i] && processes[i].arrival_time <= time) {
                        q.push(i);
                        inqueue[i] = true;
                        break;
                    }
                }
                if (q.empty()) {
                    time++; 
                    continue;
                }
            }

            int idx = q.front();
            q.pop();
            roundrobin& p = processes[idx];

            int starttime = time; 

            if (p.remaining_time > time_quantum) {
                time += time_quantum;
                p.remaining_time -= time_quantum;
            } else {
                time += p.remaining_time;
                p.remaining_time=0;
                p.completiontime=time;
                p.turnaround_time=p.completiontime-p.arrival_time;
                p.waiting_time=p.turnaround_time-p.burst_time;
                completed++;
            }

            gantt_ids.push_back({p.process_id, idx});
            gantt_times.push_back({starttime, time});

            for (int i = 0; i < n; i++) {
                if (!inqueue[i] && processes[i].arrival_time <= time) {
                    q.push(i);
                    inqueue[i] = true;
                }
            }
            if (p.remaining_time>0) {
                q.push(idx);
            }
        }
    }
};

int main() {
    int processnum;
    cout << "Enter the number of processes: ";
    cin >> processnum;
    vector<roundrobin> processes(processnum);
    for (int i = 0; i < processnum; i++) {
        int id, arr, bt;
        cout<<"Enter details for Process " << i + 1 << ":\n";
        cout<<"Process ID: "; 
        cin>>id;
        cout<< "Arrival Time: "; 
        cin>>arr;
        cout<< "Burst Time: "; 
        cin>> bt;
        processes[i] = roundrobin(id, arr, bt);
    }

    int time_quantum;
    cout<<"Enter the Time Quantum: ";
    cin>>time_quantum;

    for(auto& p : processes) {
        p.rrtimequanta(time_quantum);
    }

    vector<pair<int,int>> gantt_ids;   
    vector<pair<int,int>> gantt_times; 

    rrcalculation rr;
    rr.queuecalculation(processes, time_quantum, gantt_ids, gantt_times);
    cout<<"\nFinal Process Table:\n";
    processes[0].printrr(processes);
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < gantt_ids.size(); i++) {
        cout << "| P" << gantt_ids[i].first << " ";
    }
    cout << "|\n";
    cout << gantt_times[0].first;
    for (int i = 0; i < gantt_times.size(); i++) {
        cout << "    " << gantt_times[i].second;
    }
    cout << endl;

    return 0;
}
