
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

class Node {
public:
    int id;
    string location;
    int severity;
    int height;

    Node* left;
    Node* right;

    Node(int i, string loc, int s) {
        id = i;
        location = loc;
        severity = s;
        height = 1;
        left = right = NULL;
    }
};

class AVL {
private:
    Node* root;

    int getHeight(Node* node) {
        if (node == NULL)
            return 0;

        return node->height;
    }

    int getBalance(Node* node) {
        if (node == NULL)
            return 0;

        return getHeight(node->left) -
               getHeight(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        y->height = 1 + max(getHeight(y->left),
                            getHeight(y->right));

        x->height = 1 + max(getHeight(x->left),
                            getHeight(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        x->height = 1 + max(getHeight(x->left),
                            getHeight(x->right));

        y->height = 1 + max(getHeight(y->left),
                            getHeight(y->right));

        return y;
    }

    Node* insert(Node* node, int id,
                 string location, int severity) {

        if (node == NULL)
            return new Node(id, location, severity);

        if (id < node->id)
            node->left = insert(node->left, id,
                                location, severity);

        else if (id > node->id)
            node->right = insert(node->right, id,
                                 location, severity);

        else
            return node;

        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));

        int balance = getBalance(node);

        // LL Case
        if (balance > 1 && id < node->left->id) {
            cout << "LL Rotation\n";
            return rightRotate(node);
        }

        // RR Case
        if (balance < -1 && id > node->right->id) {
            cout << "RR Rotation\n";
            return leftRotate(node);
        }

        // LR Case
        if (balance > 1 && id > node->left->id) {
            cout << "LR Rotation\n";
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Case
        if (balance < -1 && id < node->right->id) {
            cout << "RL Rotation\n";
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != NULL)
            node = node->left;

        return node;
    }

    Node* deleteNode(Node* node, int id) {
        if (node == NULL)
            return node;

        if (id < node->id)
            node->left = deleteNode(node->left, id);

        else if (id > node->id)
            node->right = deleteNode(node->right, id);

        else {
            // Node with zero or one child
            if (node->left == NULL ||
                node->right == NULL) {

                Node* temp;

                if (node->left != NULL)
                    temp = node->left;
                else
                    temp = node->right;

                if (temp == NULL) {
                    delete node;
                    return NULL;
                }
                else {
                    Node* old = node;
                    node = temp;
                    delete old;
                }
            }

            // Node with two children
            else {
                Node* temp = findMin(node->right);

                node->id = temp->id;
                node->location = temp->location;
                node->severity = temp->severity;

                node->right = deleteNode(node->right,
                                         temp->id);
            }
        }

        if (node == NULL)
            return node;

        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));

        int balance = getBalance(node);

        // LL Case
        if (balance > 1 &&
            getBalance(node->left) >= 0)
            return rightRotate(node);

        // LR Case
        if (balance > 1 &&
            getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RR Case
        if (balance < -1 &&
            getBalance(node->right) <= 0)
            return leftRotate(node);

        // RL Case
        if (balance < -1 &&
            getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* search(Node* node, int id) {
        if (node == NULL || node->id == id)
            return node;

        if (id < node->id)
            return search(node->left, id);

        return search(node->right, id);
    }

    void inorder(Node* node) {
        if (node == NULL)
            return;

        inorder(node->left);

        cout << "ID: " << node->id
             << " | Location: " << node->location
             << " | Severity: " << node->severity
             << " | Height: " << node->height
             << " | Balance Factor: " << getBalance(node)
             << endl;

        inorder(node->right);
    }

    void levelOrder(Node* node) {
        if (node == NULL)
            return;

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            cout << current->id << " ";

            if (current->left != NULL)
                q.push(current->left);

            if (current->right != NULL)
                q.push(current->right);
        }
    }

    void displayTree(Node* node, int space) {
        if (node == NULL)
            return;

        space += 5;

        displayTree(node->right, space);

        cout << endl;

        for (int i = 5; i < space; i++)
            cout << " ";

        cout << node->id << endl;

        displayTree(node->left, space);
    }

public:
    AVL() {
        root = NULL;
    }

    void insert(int id, string location, int severity) {
        root = insert(root, id, location, severity);
    }

    void deleteEmergency(int id) {
        if (search(root, id) == NULL) {
            cout << "\nEmergency ID not found!\n";
            return;
        }

        root = deleteNode(root, id);
        cout << "\nEmergency deleted successfully.\n";
    }

    void searchEmergency(int id) {
        Node* result = search(root, id);

        if (result != NULL) {
            cout << "\nEmergency Found!\n";
            cout << "ID: " << result->id
                 << " | Location: " << result->location
                 << " | Severity: " << result->severity
                 << endl;
        }
        else {
            cout << "\nEmergency Not Found!\n";
        }
    }

    void displayInorder() {
        cout << "\nINORDER TRAVERSAL\n";
        inorder(root);
    }

    void displayLevelOrder() {
        cout << "\nLEVEL ORDER (BFS) TRAVERSAL\n";
        levelOrder(root);
        cout << endl;
    }

    void showTree() {
        cout << "\nFINAL BALANCED AVL TREE\n";
        displayTree(root, 0);
        cout << endl;
    }
};

int main() {
    AVL rescue;

    cout << "EMERGENCY RESCUE OPERATIONS\n";

    // Inserting 12 emergency records
    rescue.insert(63, "Islamabad", 5);
    rescue.insert(49, "Lahore", 4);
    rescue.insert(23, "Karachi", 3);
    rescue.insert(45, "Multan", 5);
    rescue.insert(38, "Peshawar", 2);
    rescue.insert(39, "Quetta", 4);
    rescue.insert(7, "Faisalabad", 3);
    rescue.insert(59, "Rawalpindi", 5);
    rescue.insert(15, "Sialkot", 2);
    rescue.insert(60, "Hyderabad", 4);
    rescue.insert(92, "Gujranwala", 3);
    rescue.insert(91, "Abbottabad", 5);

    rescue.searchEmergency(59);

    rescue.displayInorder();

    rescue.displayLevelOrder();

    // Delete an emergency record
    rescue.deleteEmergency(45);

    cout << "\nAFTER DELETION\n";

    rescue.displayInorder();

    rescue.displayLevelOrder();

    rescue.showTree();

    return 0;
}

