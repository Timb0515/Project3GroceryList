#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

class ItemFrequency {
private:
    map<string, int> itemCounts; // Map to store item names (string) and their frequencies (int)
    string inputFileName;        // Name of the input file
    string outputFileName;       // Name of the output (backup) file

    // Private function to load data from the input file
    bool loadData() {
        ifstream inputFile(inputFileName); // Open the input file
        if (inputFile.is_open()) {
            string item;
            while (inputFile >> item) { // Read items one by one from the file
                itemCounts[item]++; // Increment the count for the read item
            }
            inputFile.close(); // Close the input file
            return true;       // Return true if loading was successful
        }
        else {
            cerr << "Error opening input file: " << inputFileName << endl; // Output error message if file cannot be opened
            return false;      // Return false if loading failed
        }
    }

    // Private function to back up data to the output file
    bool backupData() {
        ofstream outputFile(outputFileName); // Open the output file
        if (outputFile.is_open()) {
            for (auto const& pair : itemCounts) { // Iterate through the item counts map
                outputFile << pair.first << " " << pair.second << endl; // Write item and its frequency to the output file
            }
            outputFile.close(); // Close the output file
            return true;       // Return true if backup was successful
        }
        else {
            cerr << "Error opening output file: " << outputFileName << endl; // Output error message if file cannot be opened
            return false;      // Return false if backup failed
        }
    }

public:
    // Constructor of the ItemFrequency class
    ItemFrequency(string inputFileName = "CS210_Project_Three_Input_File.txt", string outputFileName = "frequency.dat") {
        this->inputFileName = inputFileName;   // Initialize input file name
        this->outputFileName = outputFileName; // Initialize output file name
        if (!loadData() || !backupData()) { // Load data and back it up, exit if either fails
            exit(1);
        }
    }

    // Public function to get the frequency of a specific item
    int getItemFrequency(const string& item) const {
        auto it = itemCounts.find(item); // Find the item in the map
        if (it != itemCounts.end()) {
            return it->second; // Return the frequency if the item is found
        }
        else {
            return 0;          // Return 0 if the item is not found
        }
    }

    // Public function to print all item frequencies
    void printAllFrequencies() const {
        for (auto const& pair : itemCounts) { // Iterate through the item counts map
            cout << pair.first << " " << pair.second << endl; // Output item and its frequency
        }
    }

    // Public function to print a histogram of item frequencies
    void printHistogram() const {
        int maxItemLength = 0;
        for (auto const& pair : itemCounts) { // Find the maximum length of item names for formatting
            maxItemLength = max(maxItemLength, (int)pair.first.length());
        }

        for (auto const& pair : itemCounts) { // Iterate through the item counts map
            cout << setw(maxItemLength) << left << pair.first << " "; // Output item name with proper spacing
            for (int i = 0; i < pair.second; i++) { // Output asterisks representing the frequency
                cout << "*";
            }
            cout << endl;
        }
    }

    // Public function to display the menu and handle user input
    void displayMenu() {
        int choice;
        do {
            cout << "\nCorner Grocer Inventory Menu" << endl;
            cout << "1. Find Item Frequency" << endl;
            cout << "2. Print All Frequencies" << endl;
            cout << "3. Print Histogram" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) { // Check for invalid input (non-integer)
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();                                        // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
                continue;                                           // Go back to menu start
            }

            switch (choice) {
            case 1: {
                string item;
                cout << "Enter item to search: ";
                cin >> item;
                cout << "Frequency of " << item << ": " << this->getItemFrequency(item) << endl; // Output frequency of the searched item
                break;
            }
            case 2:
                this->printAllFrequencies(); // Output all item frequencies
                break;
            case 3:
                this->printHistogram(); // Output the histogram
                break;
            case 4:
                cout << "Exiting program." << endl; // Exit the program
                break;
            default:
                cout << "Invalid choice. Please try again." << endl; // Handle invalid menu choices
            }
        } while (choice != 4); // Continue until the user chooses to exit
    }
};

int main() {
    ItemFrequency inventory; // Create an ItemFrequency object
    inventory.displayMenu(); // Display the menu and handle user input

    return 0;
}