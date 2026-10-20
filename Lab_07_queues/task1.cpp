#include <iostream>
using namespace std;

const int SIZE = 5;

int queue[SIZE];
int front = -1, rear = -1;

void enqueue(int token) {
    if (rear == SIZE - 1) {
        cout << "Queue Overflow!\n";
        return;
    }

    if (front == -1)
        front = 0;

    rear++;
    queue[rear] = token;
    cout << "Customer " << token << " added.\n";
}

void dequeue() {
    if (front == -1 || front > rear) {
        cout << "Queue Underflow! No customers waiting.\n";
        return;
    }

    cout << "Serving customer: " << queue[front] << endl;
    front++;

    if (front > rear)
        front = rear = -1;
}

void display() {
    if (front == -1) {
        cout << "Queue is empty.\n";
        return;
    }

    cout << "Waiting customers: ";
    for (int i = front; i <= rear; i++)
        cout << queue[i] << " ";
    cout << endl;
}

void countCustomers() {
    if (front == -1)
        cout << "Waiting customers: 0\n";
    else
        cout << "Waiting customers: " << rear - front + 1 << endl;
}

int main() {
    int choice, token;

    do {
        cout << "\n1. Add Customer\n2. Serve Customer\n";
        cout << "3. Display Queue\n4. Count Customers\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter token number: ";
            cin >> token;
            enqueue(token);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
            break;
        case 4:
            countCustomers();
            break;
        case 5:
            cout << "Program ended.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}

