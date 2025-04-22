#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Structure for a School
struct School {
    string name, address, city, state, county;
    School* next;
    School* left;
    School* right;

    School(string n, string a, string c, string s, string co)
        : name(n), address(a), city(c), state(s), county(co), next(nullptr), left(nullptr), right(nullptr) {}
};

// Linked List
class SchoolList {
    School* head;
public:
    SchoolList() : head(nullptr) {}

    void insertLast(School* school) {
        if (!head) head = school;
        else {
            School* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = school;
        }
    }

    School* findByName(const string& name) {
        School* current = head;
        while (current) {
            if (current->name == name) return current;
            current = current->next;
        }
        return nullptr;
    }

    void display() {
        School* temp = head;
        while (temp) {
            cout << temp->name << " -> ";
            temp = temp->next;
        }
        cout << "nullptr\n";
    }
};

// Binary Search Tree
class SchoolBST {
    School* root;

    School* insert(School* node, School* newSchool) {
        if (!node) return newSchool;
        if (newSchool->name < node->name)
            node->left = insert(node->left, newSchool);
        else
            node->right = insert(node->right, newSchool);
        return node;
    }

    School* findMin(School* node) {
        while (node->left) node = node->left;
        return node;
    }

    School* deleteByName(School* node, const string& name) {
        if (!node) return nullptr;
        if (name < node->name)
            node->left = deleteByName(node->left, name);
        else if (name > node->name)
            node->right = deleteByName(node->right, name);
        else {
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

    School* findByName(School* node, const string& name) {
        if (!node || node->name == name) return node;
        if (name < node->name) return findByName(node->left, name);
        return findByName(node->right, name);
    }

public:
    SchoolBST() : root(nullptr) {}

    void insertRec(School* school) {
        root = insert(root, school);
    }

    void deleteRec(const string& name) {
        root = deleteByName(root, name);
    }

    School* searchByName(const string& name) {
        return findByName(root, name);
    }
};

// Hash Table
class SchoolHashTable {
    static const int TABLE_SIZE = 101;
    School* table[TABLE_SIZE];

    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) hash += ch;
        return hash % TABLE_SIZE;
    }

public:
    SchoolHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
    }

    void insert(School* school) {
        int index = hashFunction(school->name);
        school->next = table[index];
        table[index] = school;
    }

    void deleteByName(const string& name) {
        int index = hashFunction(name);
        School* current = table[index];
        School* prev = nullptr;

        while (current && current->name != name) {
            prev = current;
            current = current->next;
        }

        if (!current) return;

        if (!prev) table[index] = current->next;
        else prev->next = current->next;

        delete current;
    }

    School* findByName(const string& name) {
        int index = hashFunction(name);
        School* current = table[index];
        while (current) {
            if (current->name == name) return current;
            current = current->next;
        }
        return nullptr;
    }
};

// Load CSV into each structure
void loadDataset(const string& filename, SchoolList& list, SchoolBST& bst, SchoolHashTable& hash) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, address, city, state, county;
        getline(ss, name, ','); getline(ss, address, ','); getline(ss, city, ',');
        getline(ss, state, ','); getline(ss, county, ',');

        School* s1 = new School(name, address, city, state, county);
        School* s2 = new School(name, address, city, state, county);
        School* s3 = new School(name, address, city, state, county);

        list.insertLast(s1);
        bst.insertRec(s2);
        hash.insert(s3);
    }
}

int main() {
    string dataset = "Illinois_Schools.csv"; //test for time 

    SchoolList list;
    SchoolBST bst;
    SchoolHashTable hash;

    // Measure Insertion
    auto start = high_resolution_clock::now();
    loadDataset(dataset, list, bst, hash);
    auto end = high_resolution_clock::now();
    cout << "[Insertion] Total Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    string testName = "FRANKLIN PRIMARY SCHOOL";

    // Search Times
    start = high_resolution_clock::now();
    list.findByName(testName);
    end = high_resolution_clock::now();
    cout << "[Linked List] Search: " << duration_cast<microseconds>(end - start).count() << " us\n";

    start = high_resolution_clock::now();
    bst.searchByName(testName);
    end = high_resolution_clock::now();
    cout << "[BST] Search: " << duration_cast<microseconds>(end - start).count() << " us\n";

    start = high_resolution_clock::now();
    hash.findByName(testName);
    end = high_resolution_clock::now();
    cout << "[Hash Table] Search: " << duration_cast<microseconds>(end - start).count() << " us\n";

    // Deletion Times 
    start = high_resolution_clock::now();
    bst.deleteRec(testName);
    end = high_resolution_clock::now();
    cout << "[BST] Delete: " << duration_cast<microseconds>(end - start).count() << " us\n";

    start = high_resolution_clock::now();
    hash.deleteByName(testName);
    end = high_resolution_clock::now();
    cout << "[Hash Table] Delete: " << duration_cast<microseconds>(end - start).count() << " us\n";

    return 0;
}
