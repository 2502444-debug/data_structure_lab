#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node *left, *right;

    Node(string n) {
        name = n;
        left = right = NULL;
    }
};

void displayStaff(Node *root) {
    if (root == NULL)
        return;

    cout << root->name << " | Left: ";

    if (root->left != NULL)
        cout << root->left->name;
    else
        cout << "NULL";

    cout << " | Right: ";

    if (root->right != NULL)
        cout << root->right->name;
    else
        cout << "NULL";

    cout << endl;

    displayStaff(root->left);
    displayStaff(root->right);
}

void deleteStaffTree(Node *root) {
    if (root == NULL)
        return;

    deleteStaffTree(root->left);
    deleteStaffTree(root->right);
    delete root;
}

class BST {
    struct BNode {
        int id;
        BNode *left, *right;

        BNode(int value) {
            id = value;
            left = right = NULL;
        }
    };

    BNode *root;

    BNode* insertNode(BNode *node, int id, bool &inserted) {
        if (node == NULL) {
            inserted = true;
            return new BNode(id);
        }

        if (id < node->id)
            node->left = insertNode(node->left, id, inserted);
        else if (id > node->id)
            node->right = insertNode(node->right, id, inserted);

        return node;
    }

    bool searchNode(BNode *node, int id, int &visits) {
        if (node == NULL)
            return false;

        visits++;

        if (node->id == id)
            return true;

        if (id < node->id)
            return searchNode(node->left, id, visits);

        return searchNode(node->right, id, visits);
    }

    BNode* minimum(BNode *node) {
        while (node != NULL && node->left != NULL)
            node = node->left;

        return node;
    }

    BNode* deleteNode(BNode *node, int id, bool &deleted) {
        if (node == NULL)
            return NULL;

        if (id < node->id)
            node->left = deleteNode(node->left, id, deleted);
        else if (id > node->id)
            node->right = deleteNode(node->right, id, deleted);
        else {
            deleted = true;

            if (node->left == NULL) {
                BNode *temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == NULL) {
                BNode *temp = node->left;
                delete node;
                return temp;
            }

            BNode *successor = minimum(node->right);
            node->id = successor->id;

            bool ignored = false;
            node->right = deleteNode(
                node->right, successor->id, ignored
            );
        }

        return node;
    }

    void inorderNode(BNode *node) {
        if (node == NULL)
            return;

        inorderNode(node->left);
        cout << node->id << " ";
        inorderNode(node->right);
    }

    void clear(BNode *node) {
        if (node == NULL)
            return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() {
        root = NULL;
    }

    ~BST() {
        clear(root);
    }

    void insert(int id) {
        bool inserted = false;
        root = insertNode(root, id, inserted);

        if (inserted)
            cout << id << " inserted successfully.\n";
        else
            cout << "Duplicate ID rejected: " << id << endl;
    }

    bool search(int id, int &visits) {
        visits = 0;
        return searchNode(root, id, visits);
    }

    void remove(int id) {
        bool deleted = false;
        root = deleteNode(root, id, deleted);

        if (deleted)
            cout << "ID deleted successfully.\n";
        else
            cout << "ID not found.\n";

        cout << "Current IDs: ";
        inorderNode(root);
        cout << endl;
    }

    void display() {
        inorderNode(root);
        cout << endl;
    }
};

Node* createStaffTree() {
    Node *root = new Node("Principal");

    root->left = new Node("Dean");
    root->right = new Node("Registrar");

    root->left->left = new Node("HOD-CS");
    root->left->right = new Node("HOD-DS");

    root->right->left = new Node("Accountant");
    root->right->right = new Node("Librarian");

    return root;
}

void deletionTest(int id, bool makeOneChild = false) {
    BST tree;

    int ids[] = {48, 28, 68, 18, 38, 58, 78};

    for (int i = 0; i < 7; i++)
        tree.insert(ids[i]);

    if (makeOneChild)
        tree.remove(18);

    cout << "Deleting ID " << id << ":\n";
    tree.remove(id);
}

int main() {
    cout << "GENERAL BINARY TREE\n";

    Node *staff = createStaffTree();
    displayStaff(staff);
    deleteStaffTree(staff);

    cout << "\nSTAFF ID BINARY SEARCH TREE\n";

    BST tree;

    int initial[] = {48, 28, 68, 18, 38, 58, 78};

    for (int i = 0; i < 7; i++)
        tree.insert(initial[i]);

    int id, visits;

    for (int i = 1; i <= 3; i++) {
        cout << "Enter additional staff ID " << i << ": ";
        cin >> id;
        tree.insert(id);
    }

    cout << "\nEnter ID to search: ";
    cin >> id;

    if (tree.search(id, visits))
        cout << "ID exists. Node visits: " << visits << endl;
    else
        cout << "ID does not exist. Node visits: " << visits << endl;

    int tests[] = {48, 999, 1};

    for (int i = 0; i < 3; i++) {
        tree.search(tests[i], visits);

        cout << "Search " << tests[i]
             << " | Node visits: " << visits << endl;
    }

    cout << "\nEnter ID to delete: ";
    cin >> id;
    tree.remove(id);

    cout << "IDs in ascending order: ";
    tree.display();

    cout << "\nDeletion test: Leaf node\n";
    deletionTest(18);

    cout << "\nDeletion test: Node with one child\n";
    deletionTest(28, true);

    cout << "\nDeletion test: Node with two children\n";
    deletionTest(48);

    cout << "\nA general binary tree has no fixed ordering rule.\n";
    cout << "A BST keeps smaller IDs on the left and larger IDs "
         << "on the right.\n";
    cout << "Therefore, inorder traversal of a BST displays "
         << "IDs in ascending order.\n";

    return 0;
}
