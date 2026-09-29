#include <iostream>
using namespace std;

struct Node {
    string patientID;
    Node* next;
};

void addPatient(Node*& head, string id) {
    Node* newNode = new Node;
    newNode->patientID = id;
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

void displayPatients(Node* head) {
    Node* temp = head;

    while (temp != NULL) {
        cout << temp->patientID << " -> ";
        temp = temp->next;
    }

    cout << "NULL" << endl;
}

void removePatient(Node*& head) {
    if (head == NULL) {
        cout << "No patients waiting." << endl;
        return;
    }

    Node* temp = head;
    cout << temp->patientID << " is being served." << endl;

    head = head->next;
    delete temp;
}

int main() {
    Node* head = NULL;

    addPatient(head, "P101");
    addPatient(head, "P102");
    addPatient(head, "P103");
    addPatient(head, "P104");

    cout << "Waiting Patients:" << endl;
    displayPatients(head);

    removePatient(head);

    cout << "Updated Queue:" << endl;
    displayPatients(head);

    return 0;
}
