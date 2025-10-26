
/*
    Author: Cody Chase
    Date: 9/28/2025
    Unit 6 Program
    Calculate billing amount for J&J accounting firm consulting services based on hourly rate, 
        consulting time, and income status.
*/

#include <iostream>
#include <iomanip>
using namespace std;

// Constants for income and service charge rates
const double LOW_INCOME_LIMIT = 25000.0;
const double LOW_INCOME_RATE = 0.40;
const int LOW_INCOME_FREE_MINUTES = 30;
const double OTHER_RATE = 0.70;
const int OTHER_FREE_MINUTES = 20;

// Function to calculate billing amount
// hourlyRate: hourly rate in dollars
// consultingMinutes: total consulting time in minutes
// isLowIncome: true if person has low income
// Returns: billing amount in dollars
double calculateBilling(double hourlyRate, int consultingMinutes, bool isLowIncome) {
    double billing = 0.0;
    if (isLowIncome) {
        if (consultingMinutes <= LOW_INCOME_FREE_MINUTES) {
            billing = 0.0;
        } else {
            int billableMinutes = consultingMinutes - LOW_INCOME_FREE_MINUTES;
            billing = hourlyRate * LOW_INCOME_RATE * (billableMinutes / 60.0);
        }
    } else {
        if (consultingMinutes <= OTHER_FREE_MINUTES) {
            billing = 0.0;
        } else {
            int billableMinutes = consultingMinutes - OTHER_FREE_MINUTES;
            billing = hourlyRate * OTHER_RATE * (billableMinutes / 60.0);
        }
    }
    return billing;
}

int main() {
    // Input
    double hourlyRate, income;
    int consultingMinutes;
    bool isLowIncome;

    cout << "Enter the hourly rate: $";
    cin >> hourlyRate;
    cout << "Enter the total consulting time (in minutes): ";
    cin >> consultingMinutes;
    cout << "Enter the person's income: $";
    cin >> income;
    isLowIncome = (income <= LOW_INCOME_LIMIT);

    // Output income status for clarity
    cout << "Is the person low income (<= $25,000)? " << (isLowIncome ? "Yes" : "No") << endl;

    // Calculate and output billing amount
    double billingAmount = calculateBilling(hourlyRate, consultingMinutes, isLowIncome);
    cout << fixed << setprecision(2);
    cout << "Billing amount: $" << billingAmount << endl;

    return 0;
}