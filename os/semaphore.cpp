#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
class Semaphore {
private:
    string name;
    int value;
    queue<int> waiting_queue; 

public:
    Semaphore(string name, int initial_value) {
        this->name = name;
        this->value = initial_value;
    }

    void wait(int process_id) {
        cout << " -> P" << process_id << " tries to acquire " << name << "." << endl;
        value--;
        if (value < 0) {
            waiting_queue.push(process_id);
            cout << "    Value < 0 (" << value << "). P" << process_id << " is BLOCKED and added to the waiting queue." << endl;
        } else {
            cout << "    Success! P" << process_id << " has acquired the semaphore. Value is now " << value << "." << endl;
        }
    }

    void signal(int process_id) {
        cout << " -> P" << process_id << " releases " << name << "." << endl;
        value++;
        if (value <= 0) {
            if (!waiting_queue.empty()) {
                int unblocked_process = waiting_queue.front();
                waiting_queue.pop();
                cout << "    Value <= 0 (" << value << "). P" << unblocked_process << " is UNBLOCKED from the waiting queue." << endl;
            } else {
                 cout << "    Value is " << value << ", but the waiting queue is empty." << endl;
            }
        } else {
            cout << "    Semaphore released. Value is now " << value << "." << endl;
        }
    }
    
    void display_state() {
        cout << "\n---------------------------------" << endl;
        cout << "Semaphore '" << name << "' State:" << endl;
        cout << "  - Current Value: " << value << endl;
        cout << "  - Waiting Processes: ";
        if (waiting_queue.empty()) {
            cout << "None" << endl;
        } else {
            queue<int> temp = waiting_queue;
            while(!temp.empty()){
                cout << "P" << temp.front() << " ";
                temp.pop();
            }
            cout << endl;
        }
        cout << "---------------------------------\n" << endl;
    }
};

void run_simulation(Semaphore& sem) {
    int choice = 0;
    int process_id = 0;

    while (choice != 3) {
        sem.display_state();
        cout << "Choose an operation:" << endl;
        cout << "1. Wait (P operation)" << endl;
        cout << "2. Signal (V operation)" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            cout << "Enter Process ID (e.g., 1, 2, 3...): ";
            cin >> process_id;
        }

        switch (choice) {
            case 1:
                sem.wait(process_id);
                break;
            case 2:
                sem.signal(process_id);
                break;
            case 3:
                cout << "Exiting simulation." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    int type_choice;
    cout << "Select Semaphore Type:" << endl;
    cout << "1. Binary Semaphore (for mutual exclusion)" << endl;
    cout << "2. Counting Semaphore (for resource pool)" << endl;
    cout << "Enter choice: ";
    cin >> type_choice;

    if (type_choice == 1) {
        Semaphore binary_sem("Mutex", 1);
        run_simulation(binary_sem);
    } else if (type_choice == 2) {
        int count;
        cout << "Enter the initial count for the semaphore (e.g., number of resources): ";
        cin >> count;
        Semaphore counting_sem("ResourcePool", count);
        run_simulation(counting_sem);
    } else {
        cout << "Invalid choice. Exiting." << endl;
    }

    return 0;
}
