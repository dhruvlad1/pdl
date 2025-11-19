#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

int main() {
    int n, frames;
    cout << "Enter number of pages: ";
    cin >> n;
    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];
    cout << "Enter number of frames: ";
    cin >> frames;

    queue<int> q;
    unordered_set<int> s;
    int faults = 0;

    cout << "\n--- FIFO Page Replacement ---\n";
    cout << "Page\tFrames\t\tStatus\n";
    cout << "--------------------------------\n";

    for (int page : pages) {
        cout << page << "\t";
        if (s.find(page) == s.end()) {
            faults++;
            if (s.size() == frames) {
                int removed = q.front();
                q.pop();
                s.erase(removed);
            }
            s.insert(page);
            q.push(page);
            cout << "{ ";
            queue<int> temp = q;
            while (!temp.empty()) { cout << temp.front() << " "; temp.pop(); }
            cout << "}\tFAULT\n";
        } else {
            cout << "{ ";
            queue<int> temp = q;
            while (!temp.empty()) { cout << temp.front() << " "; temp.pop(); }
            cout << "}\tHIT\n";
        }
    }

    cout << "\nTotal Page Faults (FIFO): " << faults << endl;
    return 0;
}
