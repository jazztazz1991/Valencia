/*
    Author: Cody Chase
    Date: 10/12/2025
    Unit 8 Program
    This program demonstrates mastery of arrays by implementing a menu-driven
        application with three distinct features: a vote summary system, a score classification tool,
        and a climate data analyzer.
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <limits>

// --- Function Prototypes ---

// Main menu function
void displayMenu();

// Option 1: Election Summary Report
void electionSummaryReport();

// Option 2: Student Score Distribution
void studentScoreDistribution();

// Option 3: Annual Temp Tracker
void annualTempTracker();
void getData(double temps[][2], int months);
double averageHigh(const double temps[][2], int months);
double averageLow(const double temps[][2], int months);
int indexHighTemp(const double temps[][2], int months);
int indexLowTemp(const double temps[][2], int months);
std::string getMonthName(int monthIndex);

// --- Main Function ---

int main() {
    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        // Input validation
        while (std::cin.fail() || choice < 1 || choice > 4) {
            std::cout << "Invalid input. Please enter a number between 1 and 4: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> choice;
        }

        switch (choice) {
            case 1:
                electionSummaryReport();
                break;
            case 2:
                studentScoreDistribution();
                break;
            case 3:
                annualTempTracker();
                break;
            case 4:
                std::cout << "\nThank you for using this program." << std::endl;
                break;
            default:
                // This case is technically not needed due to the validation loop, but is good practice.
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
        if (choice != 4) {
            std::cout << "\nPress Enter to return to the main menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }

    } while (choice != 4);

    return 0;
}

// --- Function Implementations ---

void displayMenu() {
    std::cout << "\n----- Main Menu -----" << std::endl;
    std::cout << "1. ElectionSummaryReport" << std::endl;
    std::cout << "2. StudentScoreDistribution" << std::endl;
    std::cout << "3. AnnualTempTracker" << std::endl;
    std::cout << "4. End the program" << std::endl;
    std::cout << "Enter your choice: ";
}

// Option 1: Election Summary Report
void electionSummaryReport() {
    const int NUM_CANDIDATES = 5;
    std::string names[NUM_CANDIDATES];
    int votes[NUM_CANDIDATES];
    double totalVotes = 0;

    std::cout << "\n--- Election Summary Report ---" << std::endl;
    for (int i = 0; i < NUM_CANDIDATES; ++i) {
        std::cout << "Enter last name of candidate " << i + 1 << ": ";
        std::cin >> names[i];
        std::cout << "Enter votes for " << names[i] << ": ";
        std::cin >> votes[i];
        totalVotes += votes[i];
    }

    int maxVotes = -1;
    int winnerIndex = -1;
    for (int i = 0; i < NUM_CANDIDATES; ++i) {
        if (votes[i] > maxVotes) {
            maxVotes = votes[i];
            winnerIndex = i;
        }
    }

    std::cout << "\n" << std::left << std::setw(15) << "Candidate"
              << std::setw(20) << "Votes Received"
              << "% of Total Votes" << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < NUM_CANDIDATES; ++i) {
        double percentage = (totalVotes > 0) ? (static_cast<double>(votes[i]) / totalVotes) * 100.0 : 0.0;
        std::cout << std::left << std::setw(15) << names[i]
                  << std::setw(20) << votes[i]
                  << percentage << std::endl;
    }

    std::cout << std::left << std::setw(15) << "Total" << totalVotes << std::endl;
    if (winnerIndex != -1) {
        std::cout << "\nThe Winner of the Election is " << names[winnerIndex] << "." << std::endl;
    }
}

// Option 2: Student Score Distribution
void studentScoreDistribution() {
    std::ifstream inputFile("scores.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open scores.txt. Make sure the file is in the correct directory." << std::endl;
        return;
    }

    const int NUM_RANGES = 8;
    int scoreCounts[NUM_RANGES] = {0};
    std::string scoreRanges[NUM_RANGES] = {
        "0-24", "25-49", "50-74", "75-99", "100-124", "125-149", "150-174", "175-200"
    };

    int score;
    while (inputFile >> score) {
        if (score >= 0 && score <= 24) scoreCounts[0]++;
        else if (score >= 25 && score <= 49) scoreCounts[1]++;
        else if (score >= 50 && score <= 74) scoreCounts[2]++;
        else if (score >= 75 && score <= 99) scoreCounts[3]++;
        else if (score >= 100 && score <= 124) scoreCounts[4]++;
        else if (score >= 125 && score <= 149) scoreCounts[5]++;
        else if (score >= 150 && score <= 174) scoreCounts[6]++;
        else if (score >= 175 && score <= 200) scoreCounts[7]++;
    }
    inputFile.close();

    std::cout << "\n--- Student Score Distribution ---" << std::endl;
    std::cout << std::left << std::setw(20) << "Score Range" << "Number of Students" << std::endl;
    for (int i = 0; i < NUM_RANGES; ++i) {
        std::cout << std::left << std::setw(20) << scoreRanges[i] << scoreCounts[i] << std::endl;
    }
}

// Option 3: Annual Temp Tracker
void annualTempTracker() {
    const int MONTHS = 12;
    double temperatures[MONTHS][2]; // [][0] for high, [][1] for low

    getData(temperatures, MONTHS);

    double avgHigh = averageHigh(temperatures, MONTHS);
    double avgLow = averageLow(temperatures, MONTHS);
    int highIndex = indexHighTemp(temperatures, MONTHS);
    int lowIndex = indexLowTemp(temperatures, MONTHS);

    std::cout << "\n--- Annual Temperature Analysis ---" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average High Temperature: " << avgHigh << std::endl;
    std::cout << "Average Low Temperature:  " << avgLow << std::endl;
    std::cout << "Highest High Temp: " << temperatures[highIndex][0] << " in " << getMonthName(highIndex) << std::endl;
    std::cout << "Lowest Low Temp:   " << temperatures[lowIndex][1] << " in " << getMonthName(lowIndex) << std::endl;
}

void getData(double temps[][2], int months) {
    std::cout << "\n--- Annual Temperature Data Entry ---" << std::endl;
    for (int i = 0; i < months; ++i) {
        std::cout << "Enter high temperature for month " << i + 1 << ": ";
        std::cin >> temps[i][0];
        std::cout << "Enter low temperature for month " << i + 1 << ": ";
        std::cin >> temps[i][1];
    }
}

double averageHigh(const double temps[][2], int months) {
    double sum = 0;
    for (int i = 0; i < months; ++i) {
        sum += temps[i][0];
    }
    return (months > 0) ? sum / months : 0.0;
}

double averageLow(const double temps[][2], int months) {
    double sum = 0;
    for (int i = 0; i < months; ++i) {
        sum += temps[i][1];
    }
    return (months > 0) ? sum / months : 0.0;
}

int indexHighTemp(const double temps[][2], int months) {
    int highIndex = 0;
    for (int i = 1; i < months; ++i) {
        if (temps[i][0] > temps[highIndex][0]) {
            highIndex = i;
        }
    }
    return highIndex;
}

int indexLowTemp(const double temps[][2], int months) {
    int lowIndex = 0;
    for (int i = 1; i < months; ++i) {
        if (temps[i][1] < temps[lowIndex][1]) {
            lowIndex = i;
        }
    }
    return lowIndex;
}

std::string getMonthName(int monthIndex) {
    const std::string months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    if (monthIndex >= 0 && monthIndex < 12) {
        return months[monthIndex];
    }
    return "Invalid Month";
}
