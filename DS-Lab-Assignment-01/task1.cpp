
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int flightNo;
    string destination;
    string departureTime;
    Node* left;
    Node* right;

    Node(int no, string dest, string time) {
        flightNo = no;
        destination = dest;
        departureTime = time;
        left = right = NULL;
    }
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int no, string dest, string time) {
        if (node == NULL)
            return new Node(no, dest, time);

        if (no < node->flightNo)
            node->left = insert(node->left, no, dest, time);
        else if (no > node->flightNo)
            node->right = insert(node->right, no, dest, time);

        return node;
    }

    Node* search(Node* node, int no) {
        if (node == NULL || node->flightNo == no)
            return node;

        if (no < node->flightNo)
            return search(node->left, no);

        return search(node->right, no);
    }

    Node* findMin(Node* node) {
        while (node != NULL && node->left != NULL)
            node = node->left;

        return node;
    }

    Node* findMax(Node* node) {
        while (node != NULL && node->right != NULL)
            node = node->right;

        return node;
    }

    Node* deleteNode(Node* node, int no) {
        if (node == NULL)
            return node;

        if (no < node->flightNo)
            node->left = deleteNode(node->left, no);

        else if (no > node->flightNo)
            node->right = deleteNode(node->right, no);

        else {
            // Case 1: No child
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }

            // Case 2: One child
            else if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children
            Node* temp = findMin(node->right);

            node->flightNo = temp->flightNo;
            node->destination = temp->destination;
            node->departureTime = temp->departureTime;

            node->right = deleteNode(node->right, temp->flightNo);
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == NULL) return;

        inorder(node->left);
        displayRecord(node);
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == NULL) return;

        displayRecord(node);
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == NULL) return;

        postorder(node->left);
        postorder(node->right);
        displayRecord(node);
    }

    void displayRecord(Node* node) {
        cout << "Flight: " << node->flightNo
             << " | Destination: " << node->destination
             << " | Departure: " << node->departureTime << endl;
    }

    int countNodes(Node* node) {
        if (node == NULL) return 0;

        return 1 + countNodes(node->left)
                 + countNodes(node->right);
    }

    int height(Node* node) {
        if (node == NULL) return 0;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return 1 + max(leftHeight, rightHeight);
    }

    void displayTree(Node* node, int space) {
        if (node == NULL) return;

        space += 5;

        displayTree(node->right, space);

        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";

        cout << node->flightNo << endl;

        displayTree(node->left, space);
    }

public:
    BST() {
        root = NULL;
    }

    void insert(int no, string dest, string time) {
        root = insert(root, no, dest, time);
    }

    void searchFlight(int no) {
        Node* result = search(root, no);

        if (result != NULL) {
            cout << "\nFlight Found:\n";
            displayRecord(result);
        }
        else {
            cout << "\nFlight Not Found!\n";
        }
    }

    void deleteFlight(int no) {
        root = deleteNode(root, no);
        cout << "\nDeletion operation completed.\n";
    }

    void displayInorder() {
        cout << "\nINORDER TRAVERSAL\n";
        inorder(root);
    }

    void displayPreorder() {
        cout << "\nPREORDER TRAVERSAL\n";
        preorder(root);
    }

    void displayPostorder() {
        cout << "\nPOSTORDER TRAVERSAL\n";
        postorder(root);
    }

    void displayMinMax() {
        Node* minimum = findMin(root);
        Node* maximum = findMax(root);

        if (minimum != NULL) {
            cout << "\nMinimum Flight Number: "
                 << minimum->flightNo;
        }

        if (maximum != NULL) {
            cout << "\nMaximum Flight Number: "
                 << maximum->flightNo;
        }

        cout << endl;
    }

    void displayCount() {
        cout << "\nTotal Flights: "
             << countNodes(root) << endl;
    }

    void displayHeight() {
        cout << "\nTree Height: "
             << height(root) << endl;
    }

    void showTree() {
        cout << "\nFINAL BST STRUCTURE\n";
        displayTree(root, 0);
        cout << endl;
    }
};

int main() {
    BST airport;

    airport.insert(100, "London", "08:00 AM");
    airport.insert(50, "Dubai", "09:00 AM");
    airport.insert(150, "Paris", "10:00 AM");
    airport.insert(30, "Tokyo", "11:00 AM");
    airport.insert(70, "New York", "12:00 PM");
    airport.insert(130, "Toronto", "01:00 PM");
    airport.insert(170, "Sydney", "02:00 PM");
    airport.insert(20, "Berlin", "03:00 PM");
    airport.insert(40, "Rome", "04:00 PM");
    airport.insert(60, "Madrid", "05:00 PM");
    airport.insert(80, "Istanbul", "06:00 PM");
    airport.insert(120, "Doha", "07:00 PM");

    cout << "AIRPORT FLIGHT SCHEDULING SYSTEM\n";

    airport.displayInorder();
    airport.displayPreorder();
    airport.displayPostorder();

    airport.searchFlight(130);

    airport.displayMinMax();
    airport.displayCount();
    airport.displayHeight();

    // Demonstrating all three deletion cases
    airport.deleteFlight(20);   // Leaf node
    airport.deleteFlight(30);   // One child
    airport.deleteFlight(100);  // Two children

    airport.displayCount();
    airport.showTree();

    return 0;
}

