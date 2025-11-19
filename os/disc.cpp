#include <bits/stdc++.h>
using namespace std;
#define CYLINDERS 5000
#define REQUESTS 1000

// Generate random requests
vector<int> generateRequests() {
    vector<int> req(REQUESTS);
    srand(time(0));
    for (int i = 0; i < REQUESTS; i++)
        req[i] = rand() % CYLINDERS;
    return req;
}

// FCFS
int FCFS(vector<int> req, int head) {
    int total = 0;
    for (int r : req) {
        total += abs(head - r);
        head = r;
    }
    return total;
}

// SSTF
int SSTF(vector<int> req, int head) {
    int total = 0;
    vector<bool> done(req.size(), false);
    for (int count = 0; count < req.size(); count++) {
        int idx = -1, mindist = INT_MAX;
        for (int i = 0; i < req.size(); i++) {
            if (!done[i] && abs(req[i] - head) < mindist) {
                mindist = abs(req[i] - head);
                idx = i;
            }
        }
        done[idx] = true;
        total += abs(req[idx] - head);
        head = req[idx];
    }
    return total;
}

// SCAN
int SCAN(vector<int> req, int head, bool directionRight) {
    int total = 0;
    req.push_back(head);
    sort(req.begin(), req.end());
    int pos = find(req.begin(), req.end(), head) - req.begin();

    if (directionRight) {
        for (int i = pos + 1; i < req.size(); i++) total += abs(req[i] - head), head = req[i];
        total += abs(CYLINDERS - 1 - head);
        head = CYLINDERS - 1;
        for (int i = pos - 1; i >= 0; i--) total += abs(req[i] - head), head = req[i];
    } else {
        for (int i = pos - 1; i >= 0; i--) total += abs(req[i] - head), head = req[i];
        total += abs(head - 0);
        head = 0;
        for (int i = pos + 1; i < req.size(); i++) total += abs(req[i] - head), head = req[i];
    }
    return total;
}

// C-SCAN
int CSCAN(vector<int> req, int head) {
    int total = 0;
    req.push_back(head);
    sort(req.begin(), req.end());
    int pos = find(req.begin(), req.end(), head) - req.begin();

    for (int i = pos + 1; i < req.size(); i++) total += abs(req[i] - head), head = req[i];
    total += abs(CYLINDERS - 1 - head);
    total += CYLINDERS - 1;
    head = 0;
    for (int i = 0; i < pos; i++) total += abs(req[i] - head), head = req[i];
    return total;
}

// LOOK
int LOOK(vector<int> req, int head, bool directionRight) {
    int total = 0;
    req.push_back(head);
    sort(req.begin(), req.end());
    int pos = find(req.begin(), req.end(), head) - req.begin();

    if (directionRight) {
        for (int i = pos + 1; i < req.size(); i++) total += abs(req[i] - head), head = req[i];
        for (int i = pos - 1; i >= 0; i--) total += abs(req[i] - head), head = req[i];
    } else {
        for (int i = pos - 1; i >= 0; i--) total += abs(req[i] - head), head = req[i];
        for (int i = pos + 1; i < req.size(); i++) total += abs(req[i] - head), head = req[i];
    }
    return total;
}

// C-LOOK
int CLOOK(vector<int> req, int head) {
    int total = 0;
    req.push_back(head);
    sort(req.begin(), req.end());
    int pos = find(req.begin(), req.end(), head) - req.begin();

    for (int i = pos + 1; i < req.size(); i++) total += abs(req[i] - head), head = req[i];
    total += abs(head - req[0]);
    head = req[0];
    for (int i = 0; i < pos; i++) total += abs(req[i] - head), head = req[i];
    return total;
}

// Main
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <initial_head_position>\n";
        return 1;
    }
    int head = stoi(argv[1]);
    vector<int> requests = generateRequests();

    cout << "Initial Head Position: " << head << "\n";
    cout << "Total Head Movements:\n";
    cout << "FCFS:   " << FCFS(requests, head) << endl;
    cout << "SSTF:   " << SSTF(requests, head) << endl;
    cout << "SCAN:   " << SCAN(requests, head, true) << endl;
    cout << "C-SCAN: " << CSCAN(requests, head) << endl;
    cout << "LOOK:   " << LOOK(requests, head, true) << endl;
    cout << "C-LOOK: " << CLOOK(requests, head) << endl;
    return 0;
}