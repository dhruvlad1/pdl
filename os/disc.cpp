/* #include <bits/stdc++.h>
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
*/

#include <bits/stdc++.h>
using namespace std;

// ---------- FCFS ----------
int FCFS(vector<int> requests, int head) {
    int total = 0;
    for (int r : requests) {
        total += abs(r - head);
        head = r;
    }
    return total;
}

// ---------- SSTF ----------
int SSTF(vector<int> requests, int head) {
    int total = 0;
    vector<bool> visited(requests.size(), false);

    for (int i = 0; i < requests.size(); i++) {
        int idx = -1, dist = INT_MAX;
        for (int j = 0; j < requests.size(); j++) {
            if (!visited[j] && abs(requests[j] - head) < dist) {
                dist = abs(requests[j] - head);
                idx = j;
            }
        }
        visited[idx] = true;
        total += abs(requests[idx] - head);
        head = requests[idx];
    }
    return total;
}

// ---------- SCAN ----------
int SCAN(vector<int> requests, int head, int disk_size) {
    vector<int> left, right;
    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    left.push_back(0);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int total = 0;
    int cur = head;

    for (int r : right) {
        total += abs(cur - r);
        cur = r;
    }

    total += abs(cur - left.back());
    cur = left.back();

    for (int i = left.size() - 2; i >= 0; i--) {
        total += abs(cur - left[i]);
        cur = left[i];
    }

    return total;
}

// ---------- C-SCAN ----------
int CSCAN(vector<int> requests, int head, int disk_size) {
    vector<int> left, right;
    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int total = 0;
    int cur = head;

    for (int r : right) {
        total += abs(cur - r);
        cur = r;
    }

    total += abs(cur - (disk_size - 1));
    total += (disk_size - 1);

    cur = 0;

    for (int r : left) {
        total += abs(cur - r);
        cur = r;
    }

    return total;
}

// ---------- LOOK ----------
int LOOK(vector<int> requests, int head) {
    vector<int> left, right;

    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int total = 0;
    int cur = head;

    for (int r : right) {
        total += abs(cur - r);
        cur = r;
    }

    for (int i = left.size() - 1; i >= 0; i--) {
        total += abs(cur - left[i]);
        cur = left[i];
    }

    return total;
}

// ---------- C-LOOK ----------
int CLOOK(vector<int> requests, int head) {
    vector<int> left, right;

    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int total = 0;
    int cur = head;

    for (int r : right) {
        total += abs(cur - r);
        cur = r;
    }

    if (!left.empty()) {
        total += abs(cur - left.front());
        cur = left.front();

        for (int r : left) {
            total += abs(cur - r);
            cur = r;
        }
    }

    return total;
}

// ---------- MAIN ----------
int main() {
    int disk_size = 5000;
    int num_requests = 1000;
    int head;

    cout << "Enter initial head position: ";
    cin >> head;

    srand(time(0));
    vector<int> requests(num_requests);
    for (int i = 0; i < num_requests; i++)
        requests[i] = rand() % disk_size;

    cout << "\nGenerated " << num_requests << " random requests (0-" 
         << disk_size - 1 << ")\n";
    cout << "Initial Head Position: " << head << "\n";

    cout << "\nTotal Head Movements:\n";
    cout << "FCFS     : " << FCFS(requests, head) << "\n";
    cout << "SSTF     : " << SSTF(requests, head) << "\n";
    cout << "SCAN     : " << SCAN(requests, head, disk_size) << "\n";
    cout << "C-SCAN   : " << CSCAN(requests, head, disk_size) << "\n";
    cout << "LOOK     : " << LOOK(requests, head) << "\n";
    cout << "C-LOOK   : " << CLOOK(requests, head) << "\n";

    return 0;
}



