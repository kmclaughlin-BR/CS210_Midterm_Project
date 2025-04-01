/*
 * Katie McLaughlin
 * CS 210 - 2025 SP
 * Midterm Project
 */



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Structure for a School
struct School {
    string name;
    string address;
    string city;
    string state;
    string county;
    School* next;
    School* left;
    School* right;

    // Constructor
    School(string n, string a, string c, string s, string co) {
        name = n;
        address = a;
        city = c;
        state = s;
        county = co;
        next = nullptr;
        left = right = nullptr;
    }
};

class SchoolBST {
    School* root;

    // Insert helper function (recursive)
    School* insert(School* node, School* newSchool) {
        if (node == nullptr) return newSchool;
        if (newSchool->name < node->name) {
            node->left = insert(node->left, newSchool);
        } else {
            node->right = insert(node->right, newSchool);
        }
        return node;
    }

    // Find minimum node (used for deletion)
    School* findMin(School* node) {
        while (node->left) node = node->left;
        return node;
    }

    // Delete function (recursive)
    School* deleteByName(School* node, const string& name) {
        if (!node) return nullptr;

        if (name < node->name) {
            node->left = deleteByName(node->left, name);
        } else if (name > node->name) {
            node->right = deleteByName(node->right, name);
        } else {
            if (!node->left) {
                School* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                School* temp = node->left;
                delete node;
                return temp;
            }

            School* temp = findMin(node->right);
            node->name = temp->name;
            node->address = temp->address;
            node->city = temp->city;
            node->state = temp->state;
            node->county = temp->county;
            node->right = deleteByName(node->right, temp->name);
        }
        return node;
    }

    // Search function
    School* findByName(School* node, const string& name) {
        if (!node || node->name == name) return node;
        if (name < node->name) return findByName(node->left, name);
        return findByName(node->right, name);
    }

    // Traversal functions
    void displayInOrder(School* node) {
        if (!node) return;
        displayInOrder(node->left);
        cout << node->name << " -> ";
        displayInOrder(node->right);
    }

    void displayPreOrder(School* node) {
        if (!node) return;
        cout << node->name << " -> ";
        displayPreOrder(node->left);
        displayPreOrder(node->right);
    }

    void displayPostOrder(School* node) {
        if (!node) return;
        displayPostOrder(node->left);
        displayPostOrder(node->right);
        cout << node->name << " -> ";
    }

public:
    SchoolBST() : root(nullptr) {}

    void insertRec(School* school) {
        root = insert(root, school);
    }

    void deleteRec(const string& name) {
        root = deleteByName(root, name);
    }

    void searchByName(const string& name) {
        School* result = findByName(root, name);
        if (result) {
            cout << "School Found:\n";
            cout << "Name: " << result->name << endl;
            cout << "Address: " << result->address << endl;
            cout << "City: " << result->city << endl;
            cout << "State: " << result->state << endl;
            cout << "County: " << result->county << endl;
        } else {
            cout << "School with name '" << name << "' not found.\n";
        }
    }

    void displayInOrder() {
        cout << "\nIn-Order Traversal:\n";
        displayInOrder(root);
        cout << "nullptr\n";
    }

    void displayPreOrder() {
        cout << "\nPre-Order Traversal:\n";
        displayPreOrder(root);
        cout << "nullptr\n";
    }

    void displayPostOrder() {
        cout << "\nPost-Order Traversal:\n";
        displayPostOrder(root);
        cout << "nullptr\n";
    }
};

// Read CSV file and populate the BST
void readCSV(const string& filename, SchoolBST& schoolBST) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string name, address, city, state, county;

        getline(ss, name, ',');
        getline(ss, address, ',');
        getline(ss, city, ',');
        getline(ss, state, ',');
        getline(ss, county, ',');

        School* newSchool = new School(name, address, city, state, county);
        schoolBST.insertRec(newSchool);
    }

    file.close();
}



class SchoolList {
    School* head;

public:
    SchoolList() : head(nullptr) {}

    // Insert a new School at the end of the list
    void insertLast(School* school) {
        if (head == nullptr) {
            head = school;
        } else {
            School* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = school;
        }
    }

    void insertFirst(School* school) {
        school->next = head;
        head = school;
    }

    void deleteByName(const string& name) {
        if (head == nullptr) {
            cout << "The list is empty. Nothing to delete." << endl;
            return;
        }

        if (head->name == name) {
            School* temp = head;
            head = head->next;
            delete temp;
            cout << "Deleted school with name: " << name << endl;
            return;
        }

        School* current = head;
        School* prev = nullptr;

        while (current != nullptr && current->name != name) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "School with name " << name << " not found." << endl;
            return;
        }

        prev->next = current->next;
        delete current;
        cout << "Deleted school with name: " << name << endl;
    }

    // Display the linked list
    void display() {
        School* temp = head;
        while (temp != nullptr) {
            cout << temp->name << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    string filename = "CS210Names.csv";
    SchoolBST schoolBST;
    readCSV(filename, schoolBST);

    cout << "\n--- Searching for 'FRANKLIN PRIMARY SCHOOL' ---\n";
    schoolBST.searchByName("FRANKLIN PRIMARY SCHOOL");

    cout << "\nDeleting 'FRANKLIN PRIMARY SCHOOL' ...";
    schoolBST.deleteRec("FRANKLIN PRIMARY SCHOOL");
    cout << "Deleted 'FRANKLIN PRIMARY SCHOOL' (if found).\n";

    schoolBST.displayInOrder();

    schoolBST.displayPreOrder();

    schoolBST.displayPostOrder();

    return 0;
}
