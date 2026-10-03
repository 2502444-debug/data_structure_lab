#include <iostream>
#include <string>
using namespace std;

// Node class for Doubly Linked List
class Node {
public:
    string imageName;
    Node* prev;
    Node* next;

    Node(string name) {
        imageName = name;
        prev = NULL;
        next = NULL;
    }
};

// Doubly Linked List class
class ImageGallery {
private:
    Node* head;
    Node* tail;

public:
    ImageGallery() {
        head = NULL;
        tail = NULL;
    }

    // Add an image
    void addImage(string imageName) {
        Node* newNode = new Node(imageName);

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

    // Display images from first to last
    void displayForward() {
        Node* current = head;

        cout << "Image Gallery (First -> Last):" << endl;

        while (current != NULL) {
            cout << current->imageName << endl;
            current = current->next;
        }
    }

    // Display images from last to first
    void displayBackward() {
        Node* current = tail;

        cout << "\nImage Gallery (Last -> First):" << endl;

        while (current != NULL) {
            cout << current->imageName << endl;
            current = current->prev;
        }
    }
};

int main() {
    ImageGallery gallery;

    // Store 5 images
    gallery.addImage("Nature.jpg");
    gallery.addImage("Family.jpg");
    gallery.addImage("Vacation.jpg");
    gallery.addImage("Friends.jpg");
    gallery.addImage("Sunset.jpg");

    // Display from first to last
    gallery.displayForward();

    // Display from last to first
    gallery.displayBackward();

    return 0;
}
