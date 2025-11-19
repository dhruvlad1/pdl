#include <iostream>
#include <vector>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix, const string& name) {
    cout << "\n--- " << name << " Matrix ---" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

int main() {
    int n, m;

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    cout << "\nEnter the Allocation Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    vector<vector<int>> max(n, vector<int>(m));
    cout << "\nEnter the Max Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    vector<int> available(m);
    cout << "\nEnter the Available Resources:" << endl;
    for (int j = 0; j < m; j++) {
        cin >> available[j];
    }

    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    cout << "\n=========================================" << endl;
    cout << "           SYSTEM STATE" << endl;
    cout << "=========================================" << endl;
    printMatrix(allocation, "Allocation");
    printMatrix(max, "Max");
    printMatrix(need, "Need");
    cout << "\n--- Available Resources ---" << endl;
    for(int val : available) {
        cout << val << "\t";
    }
    cout << "\n\n";

    vector<bool> finish(n, false);
    vector<int> safeSequence;
    vector<int> work = available;

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence.push_back(p);
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            cout << "--> System is in an UNSAFE state." << endl;
            cout << "--> Deadlock is possible." << endl;
            return 0;
        }
    }

    cout << "--> System is in a SAFE state." << endl;
    cout << "--> Safe Sequence is: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSequence[i] << (i == n - 1 ? "" : " -> ");
    }
    cout << endl;

    return 0;
}
