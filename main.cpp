#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class CSVReader {
public:
    static void parseCSVLineByLine(const string& filename) {
        ifstream file(filename);
        string line;
        int lineCount = 0;  // To track the number of lines

        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        // Read file line by line
        while (getline(file, line)) {
            lineCount++;
            stringstream ss(line);  // Create a stringstream for the current line
            string word;
            int columnCount = 0;  // To track the number of columns in the current line

            // Parse each column (separated by commas)
            while (getline(ss, word, ',')) {
                columnCount++;
                // Process the word (column) here
                cout << "Line " << lineCount << ", Column " << columnCount << ": " << word << endl;
            }
        }

        file.close();
    }
};
template<typename T>
struct School {
    string name;
    string address;
    string city;
    string state;
    string county;
    School* next;
    T data;
    School(T val) : data(val), next(nullptr) {}

    School (string n, string a, string c, string s, string co) {
        name = n;
        address = a;
        city = c;
        state = s;
        county = co;
        next = NULL;
    }

};
template<typename T>
class SchoolList {
    School<T>* head;

    public:
    SchoolList() : head(nullptr) {}

    void insertLast(T school)
    {
        School<T>* newNode = new School<T>(data);
        if(head==nullptr)
        {
            head = newNode;
        }else
        {
            School<T>* temp = head;
            while(temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }


    void insertFirst(T school)
    {
        School<T>* newNode = new School<T>(data);
        if(head==nullptr)
        {
            head = newNode;
        }else
        {
            School<T>* temp = head;
            temp->next = newNode;
        }
    }


    void deleteByName(T name) {
        if (head == nullptr) {
            cout << "List is empty. Nothing to delete." << endl;
            return;
        }
        if (head->data == name) {
            School<T>* temp = head;
            head = head->next;
            delete temp;
            cout << "Deleted school with name: " << name << endl;
            return;
        }
        School<T>* current = head;
        School<T>* prev = nullptr;

        while (current != nullptr && current->data != name) {
            prev = current;
            current = current->next;
        }
        if (current == nullptr) {
            cout << "Scool with name " << name << " not found." << endl;
            return;
        }
        prev->next = current->next;
        delete current;
        cout << "Deleted school with name: " << name << endl;
    }





    void display()
    {
        School<T>* temp = head;
        while(temp!=nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

};



int main() {
    string filename = "CS210Names.csv";  // Your CSV file name
    CSVReader::parseCSVLineByLine(filename);  // Call function to parse the file

    return 0;
}
