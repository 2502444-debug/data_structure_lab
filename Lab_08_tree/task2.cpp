
#include <iostream>
using namespace std;

class BST {
    struct Node {
        int id;
        Node *left, *right;

        Node(int value) {
            id = value;
            left = right = NULL;
        }
    };

    Node *root;

    Node* insertNode(Node *node, int id, bool &inserted) {
        if (node == NULL) {
            inserted = true;
            return new Node(id);
        }

        if (id < node->id)
            node->left = insertNode(node->left, id, inserted);
        else if (id > node->id)
            node->right = insertNode(node->right, id, inserted);

        return node;
    }

    Node* searchNode(Node *node, int id) {
        if (node == NULL || node->id == id)
            return node;

        if (id < node->id)
            return searchNode(node->left, id);

        return searchNode(node->right, id);
    }

    Node* minimum(Node *node) {
        while (node != NULL && node->left != NULL)
            node = node->left;

        return node;
    }

    Node* deleteNode(Node *node, int id, bool &deleted) {
        if (node == NULL)
            return NULL;

        if (id < node->id)
            node->left = deleteNode(node->left, id, deleted);
        else if (id > node->id)
            node->right = deleteNode(node->right, id, deleted);
        else {
            deleted = true;

            if (node->left == NULL) {
                Node *temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == NULL) {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *successor = minimum(node->right);
            node->id = successor->id;

            bool ignored = false;
            node->right = deleteNode(
                node->right, successor->id, ignored
            );
        }

        return node;
    }

    void inorder(Node *node) {
        if (node == NULL)
            return;

        inorder(node->left);
        cout << node->id << " ";
        inorder(node->right);
    }

    void preorder(Node *node) {
        if (node == NULL)
            return;

        cout << node->id << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node *node) {
        if (node == NULL)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->id << " ";
    }

    int countNodes(Node *node) {
        if (node == NULL)
            return 0;

        return 1 + countNodes(node->left)
                 + countNodes(node->right);
    }

    int height(Node *node) {
        if (node == NULL)
            return 0;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return 1 + (leftHeight > rightHeight
                    ? leftHeight : rightHeight);
    }

    void clear(Node *node) {
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
            cout << "ID inserted successfully.\n";
        else
            cout << "Duplicate ID. Tree unchanged.\n";
    }

    void search(int id) {
        if (root == NULL) {
            cout << "Tree is empty.\n";
            return;
        }

        if (searchNode(root, id) != NULL)
            cout << "ID found.\n";
        else
            cout << "ID not found.\n";
    }

    void remove(int id) {
        bool deleted = false;
        root = deleteNode(root, id, deleted);

        if (deleted)
            cout << "ID deleted. Updated IDs: ";
        else
            cout << "ID not found. Current IDs: ";

        inorder(root);
        cout << endl;
    }

    void showInorder() {
        if (root == NULL)
            cout << "Tree is empty.";
        else
            inorder(root);

        cout << endl;
    }

    void showPreorder() {
        if (root == NULL)
            cout << "Tree is empty.";
        else
            preorder(root);

        cout << endl;
    }

    void showPostorder() {
        if (root == NULL)
            cout << "Tree is empty.";
        else
            postorder(root);

        cout << endl;
    }

    void showCount() {
        cout << "Total nodes: " << countNodes(root) << endl;
    }

    void showHeight() {
        cout << "Tree height (levels): "
             << height(root) << endl;
    }
};

int main() {
    BST tree;

    int initial[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};

    for (int i = 0; i < 9; i++)
        tree.insert(initial[i]);

    int choice = 0, id;

    do {
        cout << "\n--- HOSPITAL INVENTORY BST ---\n";
        cout << "1. Insert an ID\n";
        cout << "2. Search for an ID\n";
        cout << "3. Delete an ID\n";
        cout << "4. In-order traversal\n";
        cout << "5. Pre-order traversal\n";
        cout << "6. Post-order traversal\n";
        cout << "7. Count total nodes\n";
        cout << "8. Calculate tree height\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter 1 to 9.\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter ID: ";
            if (cin >> id)
                tree.insert(id);
            else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid ID.\n";
            }
            break;

        case 2:
            cout << "Enter ID to search: ";
            if (cin >> id)
                tree.search(id);
            else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid ID.\n";
            }
            break;

        case 3:
            cout << "Enter ID to delete: ";
            if (cin >> id)
                tree.remove(id);
            else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid ID.\n";
            }
            break;

        case 4:
            cout << "In-order: ";
            tree.showInorder();
            break;

        case 5:
            cout << "Pre-order: ";
            tree.showPreorder();
            break;

        case 6:
            cout << "Post-order: ";
            tree.showPostorder();
            break;

        case 7:
            tree.showCount();
            break;

        case 8:
            tree.showHeight();
            break;

        case 9:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice. Select 1 to 9.\n";
        }

    } while (choice != 9);

    return 0;
}

