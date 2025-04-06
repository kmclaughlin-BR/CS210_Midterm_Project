int main() {
    string filename = "CS210Names.csv";

    SchoolHashTable schoolHashTable;

    // Load data into hash table
    ifstream file(filename);
    string line;
    if (!file.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return 1;
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
        schoolHashTable.insert(newSchool);
    }

    file.close();

    // Demo operations
    cout << "\n--- Searching for 'FRANKLIN PRIMARY SCHOOL' ---\n";
    schoolHashTable.findByName("FRANKLIN PRIMARY SCHOOL");

    cout << "\n--- Deleting 'FRANKLIN PRIMARY SCHOOL' ---\n";
    schoolHashTable.deleteByName("FRANKLIN PRIMARY SCHOOL");

    cout << "\n--- Displaying Hash Table ---\n";
    schoolHashTable.display();

    return 0;
}
