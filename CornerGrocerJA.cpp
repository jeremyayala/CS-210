/// Jeremy Ayala - SNHU - 06/22/25

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

// Class Declaration
class Groceries {
private:
    string fileIn;
    string fileOut;
    string name;
    int quantity;
    map<string, int> groceryMap;

public:
    // Constructors
    Groceries();
    Groceries(string fileIn, string fileOut);

    // Menu options
    void MenuSelection1();
    void MenuSelection2();
    void MenuSelection3();

    // Reads records from input file
    void ItemInInventory();
};

// Constructor with no values
Groceries::Groceries() {
    fileIn = "CS210_Project_Three_Input_File.txt";
    fileOut = "frequency.dat";
    name = "";
    quantity = 0;
}

// Constructor with values
Groceries::Groceries(string input, string output) {
    fileIn = input;
    fileOut = output;
    name = "";
    quantity = 0;
}

//  Menu selection 1... this includes the logic for the value search
void Groceries::MenuSelection1() {
    bool exit = false;

    while (!exit) {
        cout << "Please enter a grocery item to search for or [q] to quit... ";
        cin >> name;

        // Check for 'q' before processing.... this quits to the main menu
        if (name == "q") {
            exit = true;
            break;
        }

        try {
            for (char a : name) {
                if (!isalpha(a)) {
                    throw invalid_argument("Please enter a valid alpha value.");
                }
            }

            if (groceryMap.find(name) != groceryMap.end()) {
                cout << "Located! There are " << groceryMap[name] << " " << name << "(s)." << endl;
            } else {
                throw invalid_argument("Could not find any " + name + ". Please check your spelling. Groceries start with an uppercase letter.");
            }
        } catch (invalid_argument& e) {
            cout << "ERROR!! - " << e.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.clear();
        }

        cout << endl;
    }
}

// Print the file after its been passed to the map
void Groceries::MenuSelection2() {
    for (const auto& item : groceryMap) {
        cout << left << setw(30) << item.first << setfill('.') << item.second << endl;
    }
    cout << endl;
}

// Print the histogram by looping through the first item in the map and counting the values
void Groceries::MenuSelection3() {
    for (const auto& item : groceryMap) {
        cout << item.first << " ";
        for (int i = 0; i < item.second; ++i) {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl;
}

// Reads our file and adds values to the map

void Groceries::ItemInInventory() {
    string tempItem;
    ifstream inFS(fileIn);
    ofstream outFS(fileOut);

    if (!inFS.is_open()) {
        cout << "Cannot open input file " << fileIn << endl;
        return;
    }

    if (!outFS.is_open()) {
        cout << "Cannot open output file " << fileOut << endl;
        return;
    }

    while (inFS >> tempItem) { // adding values to map 
        ++groceryMap[tempItem];
    }

    for (const auto& item : groceryMap) { /// outputting key pair values to the file
        outFS << item.first << " " << item.second << endl;
    }

    inFS.close();
    outFS.close();
}

// 
string Asterisk(int count, char s) {
    return string(count, s);
}

// Display menu options
void DisplayMenuOption() {
    cout << Asterisk(50, '*') << endl;
    cout << "Please select an option, 1 through 4" << endl;
    cout << "Option 1 - Enter a grocery item" << endl;
    cout << "Option 2 - Print the input " << endl;
    cout << "Option 3 - Display our list as a Histogram" << endl;
    cout << "Option 4 - Exit the Program" << endl;
    cout << Asterisk(50, '*') << endl;
}

// Display input error message
void InputError() {
    cout << Asterisk(50, '*') << endl;
    cout << "*** Input error! Please select '1-4' ***" << endl;
    cout << Asterisk(50, '*') << endl;
}

// Main function
int main() {
    Groceries inventory;
    int selection = 0;
    bool exitProgram = false;

    inventory.ItemInInventory();

    while (!exitProgram) {
        DisplayMenuOption();
        cout << "Your selection: ";
        cin >> selection;
        
        // Validate input and prevents infinite loop when entering anything other than 1-4
        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            InputError();
            continue; // Continue the loop for a new input
        }

        cout << Asterisk(50, '#') << endl << endl;

        switch (selection) {
            case 1:
                inventory.MenuSelection1();
                break;
            case 2:
                inventory.MenuSelection2();
                break;
            case 3:
                inventory.MenuSelection3();
                break;
            case 4:
                exitProgram = true;
                break;
            default:
                 InputError();
                break;
        }
    }

    cout << "Please visit us again" << endl;
    return 0;
}
