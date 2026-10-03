#include <iostream>
#include <string>
using namespace std;

// Node class for Doubly Linked List
class Node {
public:
    string website;
    Node* prev;
    Node* next;

    Node(string name) {
        website = name;
        prev = NULL;
        next = NULL;
    }
};

// Doubly Linked List class
class BrowserHistory {
private:
    Node* head;
    Node* tail;

public:
    BrowserHistory() {
        head = NULL;
        tail = NULL;
    }

    // Add a website to the history
    void addWebsite(string website) {
        Node* newNode = new Node(website);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Display history from first to last
    void displayForward() {
        Node* current = head;

        cout << "Browser History (First -> Last):" << endl;

        while (current != NULL) {
            cout << current->website << endl;
            current = current->next;
        }
    }

    // Display history from last to first
    void displayBackward() {
        Node* current = tail;

        cout << "\nBrowser History (Last -> First):" << endl;

        while (current != NULL) {
            cout << current->website << endl;
            current = current->prev;
        }
    }
};

int main() {
    BrowserHistory history;

    // Add 5 websites
    history.addWebsite("Google.com");
    history.addWebsite("YouTube.com");
    history.addWebsite("Wikipedia.org");
    history.addWebsite("GitHub.com");
    history.addWebsite("StackOverflow.com");

    // Display in forward direction
    history.displayForward();

    // Display in reverse direction
    history.displayBackward();

    return 0;
}
