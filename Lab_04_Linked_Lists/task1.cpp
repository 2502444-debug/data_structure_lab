#include <iostream>
using namespace std;

struct Node {
    int rollNo;
    Node* next;
};

void addStudent(Node*& head, int rollNo) {
    Node* newNode = new Node;
    newNode->rollNo = rollNo;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

void displayStudents(Node* head) {
    Node* temp = head;

    while (temp != NULL) {
        cout << temp->rollNo << " -> ";
        temp = temp->next;
    }

    cout << "NULL" << endl;
}

void searchStudent(Node* head, int rollNo) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->rollNo == rollNo) {
            cout << "Student Found" << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Student Not Found" << endl;
}

int main() {
    Node* head = NULL;

    addStudent(head, 101);
    addStudent(head, 105);
    addStudent(head, 108);
    addStudent(head, 112);

    cout << "Registered Students:" << endl;
    displayStudents(head);

    int rollNo;
    cout << "Enter Roll Number to Search: ";
    cin >> rollNo;

    searchStudent(head, rollNo);

    return 0;
}
