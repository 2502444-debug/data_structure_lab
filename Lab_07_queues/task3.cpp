
#include <iostream>
using namespace std;

const int SIZE = 5;

struct Patient {
    int id;
    int priority;
};

Patient queue[SIZE];
int count = 0;

void enqueue(int id, int priority) {
    if (count == SIZE) {
        cout << "Queue is full!\n";
        return;
    }

    int i = count - 1;

    while (i >= 0 && queue[i].priority > priority) {
        queue[i + 1] = queue[i];
        i--;
    }

    queue[i + 1].id = id;
    queue[i + 1].priority = priority;
    count++;

    cout << "Patient P" << id << " added.\n";
}

void dequeue() {
    if (count == 0) {
        cout << "No patients waiting.\n";
        return;
    }

    cout << "Treating patient P" << queue[0].id;
    cout << " with priority " << queue[0].priority << endl;

    for (int i = 0; i < count - 1; i++)
        queue[i] = queue[i + 1];

    count--;
}

void display() {
    if (count == 0) {
        cout << "No patients waiting.\n";
        return;
    }

    cout << "Waiting patients:\n";

    for (int i = 0; i < count; i++) {
        cout << "Patient P" << queue[i].id;
        cout << " - Priority " << queue[i].priority << endl;
    }
}

int main() {
    int choice, id, priority;

    do {
        cout << "\n1. Add Patient\n2. Treat Patient\n";
        cout << "3. Display Patients\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter patient ID: ";
            cin >> id;
            cout << "Enter priority (1 = highest): ";
            cin >> priority;
            enqueue(id, priority);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
            break;
        case 4:
            cout << "Program ended.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}

