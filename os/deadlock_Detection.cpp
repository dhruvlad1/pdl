#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m; // n = processes, m = resource types
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> request(n, vector<int>(m));
    vector<int> available(m);

    cout << "\nEnter Allocation Matrix (" << n << "x" << m << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];

    cout << "\nEnter Request Matrix (" << n << "x" << m << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> request[i][j];

    cout << "\nEnter Available Resources (" << m << "): ";
    for (int j = 0; j < m; j++)
        cin >> available[j];

    vector<bool> finish(n, false);
    vector<int> work = available;

    bool doneSomething;
    do {
        doneSomething = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    doneSomething = true;
                }
            }
        }
    } while (doneSomething);

    bool deadlock = false;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlock = true;
            break;
        }
    }

    cout << "\n----- Result -----\n";
    if (deadlock)
        cout << "Deadlock detected among processes: ";
    else
        cout << "No Deadlock detected. System is in safe state.\n";

    if (deadlock) {
        for (int i = 0; i < n; i++)
            if (!finish[i])
                cout << "P" << i << " ";
        cout << endl;
    }

    return 0;
}
