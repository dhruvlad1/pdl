#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
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

    list<int> lru;
    unordered_map<int, list<int>::iterator> pos;
    int faults = 0;

    cout << "\n--- LRU Page Replacement ---\n";
    cout << "Page\tFrames\t\tStatus\n";
    cout << "--------------------------------\n";

    for (int page : pages) {
        cout << page << "\t";
        if (pos.find(page) == pos.end()) {
            faults++;
            if (lru.size() == frames) {
                int last = lru.back();
                lru.pop_back();
                pos.erase(last);
            }
        } else {
            lru.erase(pos[page]);
        }
        lru.push_front(page);
        pos[page] = lru.begin();

        cout << "{ ";
        for (int p : lru) cout << p << " ";
        cout << "}\t" << (pos.find(page) == pos.end() ? "FAULT" : "HIT") << endl;
    }

    cout << "\nTotal Page Faults (LRU): " << faults << endl;
    return 0;
}
