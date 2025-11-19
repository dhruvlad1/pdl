#include <iostream>
#include <queue>
using namespace std;

#define BUFFER_SIZE 5

class ProducerConsumer {
private:
    queue<int> buffer;
    int maxSize;

public:
    ProducerConsumer(int size) {
        maxSize = size;
    }

    // Function to produce an item
    void produce(int item) {
        if (buffer.size() == maxSize) {
            cout << "Buffer is full! Producer waiting...\n";
        } else {
            buffer.push(item);
            cout << "Producer produced item " << item << endl;
        }
    }

    // Function to consume an item
    void consume() {
        if (buffer.empty()) {
            cout << "Buffer is empty! Consumer waiting...\n";
        } else {
            int item = buffer.front();
            buffer.pop();
            cout << "Consumer consumed item " << item << endl;
        }
    }

    // Function to display current buffer status
    void displayBuffer() {
        cout << "Current Buffer: [ ";
        queue<int> temp = buffer;
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << "]\n";
    }
};

int main() {
    ProducerConsumer pc(BUFFER_SIZE);
    int choice, item;

    cout << "---- Producer Consumer Simulation ----\n";
    cout << "1. Produce Item\n";
    cout << "2. Consume Item\n";
    cout << "3. Display Buffer\n";
    cout << "4. Exit\n";

    while (true) {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter item to produce: ";
            cin >> item;
            pc.produce(item);
            break;

        case 2:
            pc.consume();
            break;

        case 3:
            pc.displayBuffer();
            break;

        case 4:
            cout << "Exiting simulation...\n";
            return 0;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}
