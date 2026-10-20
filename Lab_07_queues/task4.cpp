
#include <iostream>
using namespace std;

const int SIZE = 5;

int dequeArray[SIZE];
int front = -1, rear = -1, count = 0;

void insertFront(int id) {
    if (count == SIZE) {
        cout << "Deque is full!\n";
        return;
    }

    if (count == 0)
        front = rear = 0;
    else
        front = (front - 1 + SIZE) % SIZE;

    dequeArray[front] = id;
    count++;

    cout << "Inserted " << id << " at front.\n";
}

void insertRear(int id) {
    if (count == SIZE) {
        cout << "Deque is full!\n";
        return;
    }

    if (count == 0)
        front = rear = 0;
    else
        rear = (rear + 1) % SIZE;

    dequeArray[rear] = id;
    count++;

    cout << "Inserted " << id << " at rear.\n";
}

void removeFront() {
    if (count == 0) {
        cout << "Deque is empty!\n";
        return;
    }

    cout << "Removed from front: " << dequeArray[front] << endl;

    if (count == 1)
        front = rear = -1;
    else
        front = (front + 1) % SIZE;

    count--;
}

void removeRear() {
    if (count == 0) {
        cout << "Deque is empty!\n";
        return;
    }

    cout << "Removed from rear: " << dequeArray[rear] << endl;

    if (count == 1)
        front = rear = -1;
    else
        rear = (rear - 1 + SIZE) % SIZE;

    count--;
}

void display() {
    if (count == 0) {
        cout << "Deque is empty.\n";
        return;
    }

    cout << "Requests from front to rear: ";

    for (int i = 0; i < count; i++)
        cout << dequeArray[(front + i) % SIZE] << " ";

    cout << endl;
}

int main() {
    int choice, id;

    do {
        cout << "\n1. Insert at Front\n2. Insert at Rear\n";
        cout << "3. Remove from Front\n4. Remove from Rear\n";
        cout << "5. Display Deque\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter request ID: ";
            cin >> id;
            insertFront(id);
            break;
        case 2:
            cout << "Enter request ID: ";
            cin >> id;
            insertRear(id);
            break;
        case 3:
            removeFront();
            break;
        case 4:
            removeRear();
            break;
        case 5:
            display();
            break;
        case 6:
            cout << "Program ended.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}

