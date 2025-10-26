/*
    Author: Cody Chase
    Date: 10/12/2025
    Unit 8 Program
    This application manages football player statistics through a menu-driven interface,
        allowing users to view, search, update, and save player data.
*/ 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// Struct to hold player data
struct FootballPlayer {
    string name;
    string position;
    int touchdowns;
    int catches;
    int passingYards;
    int receivingYards;
    int rushingYards;
};

// Function Prototypes
void loadData(vector<FootballPlayer>& players, const string& fileName);
void displayData(const vector<FootballPlayer>& players);
int searchPlayer(const vector<FootballPlayer>& players, const string& playerName);
void updatePlayer(vector<FootballPlayer>& players);
void saveDataToFile(const vector<FootballPlayer>& players, const string& fileName);
void displayMenu();

int main() {
    vector<FootballPlayer> players;
    const string INPUT_FILE = "footballData.txt";
    const string OUTPUT_FILE = "footballData_updated.txt";

    loadData(players, INPUT_FILE);

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        // Input validation for menu choice
        while (cin.fail() || choice < 1 || choice > 5) {
            cout << "Invalid input. Please enter a number between 1 and 5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume the newline character

        switch (choice) {
            case 1:
                displayData(players);
                break;
            case 2: {
                cout << "Enter player name to search: ";
                string name;
                getline(cin, name);
                int index = searchPlayer(players, name);
                if (index != -1) {
                    cout << name << " found at index " << index << "." << endl;
                    cout << "Position: " << players[index].position << endl;
                    cout << "Touchdowns: " << players[index].touchdowns << endl;
                    cout << "Catches: " << players[index].catches << endl;
                    cout << "Passing Yards: " << players[index].passingYards << endl;
                    cout << "Receiving Yards: " << players[index].receivingYards << endl;
                    cout << "Rushing Yards: " << players[index].rushingYards << endl;
                } else {
                    cout << "Player not found." << endl;
                }
                break;
            }
            case 3:
                updatePlayer(players);
                break;
            case 4:
                saveDataToFile(players, OUTPUT_FILE);
                break;
            case 5:
                char saveChanges;
                cout << "Do you want to save changes before exiting? (Y/N): ";
                cin >> saveChanges;
                if (toupper(saveChanges) == 'Y') {
                    saveDataToFile(players, OUTPUT_FILE);
                }
                cout << "Goodbye!" << endl;
                break;
            default:
                // This case is technically not needed due to input validation, but good practice.
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        cout << endl;
    } while (choice != 5);

    return 0;
}

// Function to display the main menu
void displayMenu() {
    cout << "==== Football Player Menu ====" << endl;
    cout << "1. Display All Players" << endl;
    cout << "2. Search for Player" << endl;
    cout << "3. Update Player Data" << endl;
    cout << "4. Save Data to File" << endl;
    cout << "5. Exit" << endl;
    cout << "==============================" << endl;
}

// Function to load player data from a file
void loadData(vector<FootballPlayer>& players, const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        exit(1); // Exit if the file cannot be opened
    }

    FootballPlayer tempPlayer;
    while (getline(inFile, tempPlayer.name)) {
        getline(inFile, tempPlayer.position);
        inFile >> tempPlayer.touchdowns >> tempPlayer.catches >> tempPlayer.passingYards >> tempPlayer.receivingYards >> tempPlayer.rushingYards;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume the rest of the line
        players.push_back(tempPlayer);
    }
    inFile.close();
}

// Function to display all player data in a formatted table
void displayData(const vector<FootballPlayer>& players) {
    cout << left;
    cout << "------------------------------------------------------------------------" << endl;
    cout << setw(15) << "Name" << setw(15) << "Position" << setw(5) << "TD" << setw(8) << "Catch"
         << setw(8) << "Pass" << setw(8) << "Recv" << setw(8) << "Rush" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    for (const auto& player : players) {
        cout << setw(15) << player.name
             << setw(15) << player.position
             << setw(5) << player.touchdowns
             << setw(8) << player.catches
             << setw(8) << player.passingYards
             << setw(8) << player.receivingYards
             << setw(8) << player.rushingYards << endl;
    }
    cout << "------------------------------------------------------------------------" << endl;
}

// Function to search for a player by name and return their index
int searchPlayer(const vector<FootballPlayer>& players, const string& playerName) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].name == playerName) {
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}

// Function to update a player's statistics
void updatePlayer(vector<FootballPlayer>& players) {
    cout << "Enter player name to update: ";
    string name;
    getline(cin, name);

    int index = searchPlayer(players, name);

    if (index != -1) {
        cout << "Enter new position: ";
        getline(cin, players[index].position);
        cout << "Enter new touchdowns: ";
        cin >> players[index].touchdowns;
        cout << "Enter new catches: ";
        cin >> players[index].catches;
        cout << "Enter new passing yards: ";
        cin >> players[index].passingYards;
        cout << "Enter new receiving yards: ";
        cin >> players[index].receivingYards;
        cout << "Enter new rushing yards: ";
        cin >> players[index].rushingYards;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume newline

        cout << "Player data updated." << endl;
    } else {
        cout << "Player not found." << endl;
    }
}

// Function to save all player data to an output file
void saveDataToFile(const vector<FootballPlayer>& players, const string& fileName) {
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error: Could not open file " << fileName << " for writing." << endl;
        return;
    }

    for (const auto& player : players) {
        outFile << player.name << endl;
        outFile << player.position << endl;
        outFile << player.touchdowns << " " << player.catches << " " << player.passingYards << " "
                << player.receivingYards << " " << player.rushingYards << endl;
    }

    outFile.close();
    cout << "Data saved to " << fileName << "." << endl;
}
