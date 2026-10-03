#include <iostream>
#include <string>
using namespace std;

// Node class for Circular Singly Linked List
class Node {
public:
    string songName;
    Node* next;

    Node(string name) {
        songName = name;
        next = NULL;
    }
};

// Circular Singly Linked List class
class MusicPlaylist {
private:
    Node* head;
    Node* tail;

public:
    MusicPlaylist() {
        head = NULL;
        tail = NULL;
    }

    // Add a song
    void addSong(string songName) {
        Node* newNode = new Node(songName);

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

    // Display all songs once
    void displayOnce() {
        if (head == NULL) {
            return;
        }

        Node* current = head;

        cout << "Music Playlist:" << endl;

        do {
            cout << current->songName << endl;
            current = current->next;
        } while (current != head);
    }

    // Play playlist for 2 complete rounds
    void playTwoRounds() {
        if (head == NULL) {
            return;
        }

        Node* current = head;

        cout << "\nPlaying Playlist for 2 Complete Rounds:" << endl;

        for (int round = 1; round <= 2; round++) {
            cout << "\nRound " << round << ":" << endl;

            for (int i = 0; i < 5; i++) {
                cout << "Playing: " << current->songName << endl;
                current = current->next;
            }
        }
    }
};

int main() {
    MusicPlaylist playlist;

    // Store 5 songs
    playlist.addSong("Song A");
    playlist.addSong("Song B");
    playlist.addSong("Song C");
    playlist.addSong("Song D");
    playlist.addSong("Song E");

    // Display all songs once
    playlist.displayOnce();

    // Play playlist for 2 complete rounds
    playlist.playTwoRounds();

    return 0;
}
