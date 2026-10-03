#include <iostream>
#include <string>
using namespace std;

// Node class for Circular Singly Linked List
class Node {
public:
    string playerName;
    Node* next;

    Node(string name) {
        playerName = name;
        next = NULL;
    }
};

// Circular Singly Linked List class
class GamePlayers {
private:
    Node* head;
    Node* tail;

public:
    GamePlayers() {
        head = NULL;
        tail = NULL;
    }

    // Add a player
    void addPlayer(string playerName) {
        Node* newNode = new Node(playerName);

        if (head == NULL) {
            head = newNode;
            tail = newNode;

            // Last node points back to first node
            tail->next = head;
        }
        else {
            tail->next = newNode;
            tail = newNode;

            // Keep the list circular
            tail->next = head;
        }
    }

    // Display each player's turn once
    void displayTurns() {
        if (head == NULL) {
            return;
        }

        Node* current = head;

        cout << "Game Player Turns:" << endl;

        do {
            cout << current->playerName << "'s turn" << endl;
            current = current->next;
        } while (current != head);

        // Show that the turn returns to the first player
        cout << "\nAfter the last player:" << endl;
        cout << current->playerName << "'s turn again" << endl;
    }
};

int main() {
    GamePlayers game;

    // Add 5 players
    game.addPlayer("Ali");
    game.addPlayer("Ahmed");
    game.addPlayer("Sara");
    game.addPlayer("Fatima");
    game.addPlayer("Usman");

    // Display turns
    game.displayTurns();

    return 0;
}
