#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int predict(vector<int>& pages, vector<int>& frames, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < frames.size(); i++) {
        int j;
        for (j = index; j < pages.size(); j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pages.size()) return i; // page not used again
    }
    return (res == -1) ? 0 : res;
}

int main() {
    int n, framesCount;
    cout << "Enter number of pages: ";
    cin >> n;
    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];
    cout << "Enter number of frames: ";
    cin >> framesCount;

    vector<int> frames;
    int faults = 0;

    cout << "\n--- Optimal Page Replacement ---\n";
    cout << "Page\tFrames\t\tStatus\n";
    cout << "--------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << pages[i] << "\t";
        if (find(frames.begin(), frames.end(), pages[i]) != frames.end()) {
            cout << "{ ";
            for (int f : frames) cout << f << " ";
            cout << "}\tHIT\n";
            continue;
        }

        faults++;
        if (frames.size() < framesCount)
            frames.push_back(pages[i]);
        else {
            int j = predict(pages, frames, i + 1);
            frames[j] = pages[i];
        }

        cout << "{ ";
        for (int f : frames) cout << f << " ";
        cout << "}\tFAULT\n";
    }

    cout << "\nTotal Page Faults (Optimal): " << faults << endl;
    return 0;
}
