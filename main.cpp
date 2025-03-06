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

int main() {
    string filename = "CS210Names.csv";  // Your CSV file name
    CSVReader::parseCSVLineByLine(filename);  // Call function to parse the file

    return 0;
}
