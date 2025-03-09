#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Structure for a School (Linked List Node)
struct School {
    string name;
    string address;
    string city;
    string state;
    string county;
    School* next;

    // Constructor
    School(string n, string a, string c, string s, string co) {
        name = n;
        address = a;
        city = c;
        state = s;
        county = co;
        next = nullptr;
    }
};

// Linked List to store Schools
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

    // Insert a new School at the beginning of the list
    void insertFirst(School* school) {
        school->next = head;
        head = school;
    }

    // Delete a School by name
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

// Function to read CSV file and populate the linked list
void readCSV(const string& filename, SchoolList& schoolList) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string name, address, city, state, county;

        // Read the CSV columns
        getline(ss, name, ',');
        getline(ss, address, ',');
        getline(ss, city, ',');
        getline(ss, state, ',');
        getline(ss, county, ',');

        // Create a new School object
        School* newSchool = new School(name, address, city, state, county);

        // Insert into the linked list
        schoolList.insertLast(newSchool);
    }

    file.close();
}

int main() {
    string filename = "CS210Names.csv";
    SchoolList schoolList;  // Create a linked list

    // Read CSV file and populate the linked list
    readCSV(filename, schoolList);

    // Display the list
    cout << "Schools in the list:" << endl;
    schoolList.display();


    return 0;
}
