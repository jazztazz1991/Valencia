/*
    Author: Cody Chase
    Date: 10/5/2025
    Unit 7 Program
    A menu-driven program that calculates federal tax based on a user's marital status, number of dependents, gross salary,
        and pension contributions.
*/
#include <iostream>
#include <string>
#include <iomanip> 

using namespace std;

// Function Prototypes
void getData(string& maritalStatus, double& grossSalary, double& pensionPercentage, int& numChildren);
double taxAmount(const string& maritalStatus, double grossSalary, double pensionPercentage, int numChildren);
void showMenu();

int main() {
    // Variables to store user information
    string maritalStatus = "";
    double grossSalary = 0.0;
    double pensionPercentage = 0.0;
    int numChildren = 0;
    int choice;

    // Main loop to display menu and process user choices
    do {
        showMenu(); // Display the main menu
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        // Process user's choice
        switch (choice) {
            case 1:
                // Get user information
                getData(maritalStatus, grossSalary, pensionPercentage, numChildren);
                break;
            case 2: // Married Couple Summary
                // Check if the user is married before displaying the summary
                if (maritalStatus == "married") {
                    double tax = taxAmount(maritalStatus, grossSalary, pensionPercentage, numChildren);
                    double pensionAmount = grossSalary * (pensionPercentage / 100.0);
                    // Display tax summary for a married couple
                    cout << "---- Tax Calculation Summary ----" << endl;
                    cout << "Marital Status: " << maritalStatus << endl;
                    cout << "Number of Children Under 14: " << numChildren << endl;
                    cout << "Gross Salary: $" << fixed << setprecision(2) << grossSalary << endl;
                    cout << "Pension Contribution: " << fixed << setprecision(0) << pensionPercentage << "% ($" << fixed << setprecision(2) << pensionAmount << ")" << endl;
                    cout << "Federal Tax Owed: $" << fixed << setprecision(2) << tax << endl;
                } else {
                    // Display an error if the marital status is not 'married'
                    cout << "Error: You selected tax summary for married individuals, but marital status is '" << (maritalStatus.empty() ? "not set" : maritalStatus) << "'." << endl;
                }
                break;
            case 3: // Single Individual Summary
                // Check if the user is single before displaying the summary
                if (maritalStatus == "single") {
                    double tax = taxAmount(maritalStatus, grossSalary, pensionPercentage, numChildren);
                    double pensionAmount = grossSalary * (pensionPercentage / 100.0);
                    // Display tax summary for a single individual
                    cout << "---- Tax Calculation Summary ----" << endl;
                    cout << "Marital Status: " << maritalStatus << endl;
                    cout << "Gross Salary: $" << fixed << setprecision(2) << grossSalary << endl;
                    cout << "Pension Contribution: " << fixed << setprecision(0) << pensionPercentage << "% ($" << fixed << setprecision(2) << pensionAmount << ")" << endl;
                    cout << "Federal Tax Owed: $" << fixed << setprecision(2) << tax << endl;
                } else {
                    // Display an error if the marital status is not 'single'
                    cout << "Error: You selected tax summary for single individuals, but marital status is '" << (maritalStatus.empty() ? "not set" : maritalStatus) << "'." << endl;
                }
                break;
            case 4:
                // End the program
                cout << "This program ended." << endl;
                break;
            default:
                // Handle invalid menu choices
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                break;
        }
        cout << endl;
    } while (choice != 4); // Loop until the user chooses to exit

    return 0; // Indicate successful execution
}

// Displays the main menu of the program
void showMenu() {
    cout << "===== Federal Tax Calculator Menu =====" << endl;
    cout << "1. Enter User Information" << endl;
    cout << "2. Tax Calculation Summary for Married Couple" << endl;
    cout << "3. Tax Calculation Summary for Single Individual" << endl;
    cout << "4. End Program" << endl;
}

// Prompts the user to enter their information and stores it in the provided variables
void getData(string& maritalStatus, double& grossSalary, double& pensionPercentage, int& numChildren) {
    cout << "Enter marital status (single/married): ";
    cin >> maritalStatus;

    // Only ask for the number of children if the user is married
    if (maritalStatus == "married") {
        cout << "Enter number of children under 14: ";
        cin >> numChildren;
    } else {
        numChildren = 0; // Reset children if not married
    }

    cout << "Enter gross salary: ";
    cin >> grossSalary;

    cout << "Enter pension fund contribution percentage (0-6%): ";
    cin >> pensionPercentage;
}

// Calculates the federal tax owed based on user information
double taxAmount(const string& maritalStatus, double grossSalary, double pensionPercentage, int numChildren) {
    double standardExemption = 0;
    double personalExemption = 0;
    
    // Determine exemptions based on marital status
    if (maritalStatus == "single") {
        standardExemption = 4000;
        personalExemption = 1500; // For the single person
    } else if (maritalStatus == "married") {
        standardExemption = 7000;
        personalExemption = 1500 * (2 + numChildren); // For the couple and children
    }

    // Calculate pension contribution and taxable income
    double pensionContribution = grossSalary * (pensionPercentage / 100.0);
    double taxableIncome = grossSalary - standardExemption - pensionContribution - personalExemption;

    // Taxable income cannot be negative
    if (taxableIncome < 0) {
        taxableIncome = 0;
    }

    // Calculate tax based on income brackets
    double tax = 0;
    if (taxableIncome >= 0 && taxableIncome <= 15000) {
        tax = taxableIncome * 0.15;
    } else if (taxableIncome > 15000 && taxableIncome <= 40000) {
        tax = 2250 + (taxableIncome - 15000) * 0.25;
    } else if (taxableIncome > 40000) {
        tax = 8460 + (taxableIncome - 40000) * 0.35;
    }

    return tax; // Return the calculated tax
}