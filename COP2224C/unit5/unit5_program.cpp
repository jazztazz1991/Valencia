/*
    Author: Cody Chase
    Date: 9/21/2025
    Unit 5 Program
    This program calculates and displays the amortization schedule for a loan.
    It simulates the repayment of a $1,000 loan with an annual interest rate
    of 7.2% and regular monthly payments of $25, tracking the principal and
    interest for each payment until the loan is fully repaid.
*/

#include <iostream> // For input/output operations
#include <iomanip>  // For output formatting

using namespace std;

int main() {
    // --- Constants and Variable Initialization ---
    const double LOAN_AMOUNT = 1000.0;
    const double ANNUAL_INTEREST_RATE = 0.072;
    const double MONTHLY_PAYMENT = 25.0;

    double balance = LOAN_AMOUNT;
    const double MONTHLY_INTEREST_RATE = ANNUAL_INTEREST_RATE / 12.0;
    int month = 0;
    double totalInterestPaid = 0.0;

    // Set output stream to display currency values with two decimal places.
    cout << fixed << setprecision(2);

    // Program and Loan Information Header
    cout << "Loan Amortization Schedule" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Loan Principal:       $" << LOAN_AMOUNT << endl;
    cout << "Annual Interest Rate: " << ANNUAL_INTEREST_RATE * 100 << "%" << endl;
    cout << "Monthly Payment:      $" << MONTHLY_PAYMENT << endl;
    cout << "--------------------------------------------------------" << endl << endl;

    // Amortization Table Header
    cout << left
         << setw(8) << "Month"
         << setw(12) << "Payment"
         << setw(12) << "Interest"
         << setw(12) << "Principal"
         << "Balance" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Main Calculation Loop
    // This loop continues as long as there is a remaining balance.
    while (balance > 0.0) {
        month++; // Increment the month counter

        // Calculate the interest accrued for the current month.
        double interestThisMonth = balance * MONTHLY_INTEREST_RATE;

        // Determine if the remaining balance can be paid off this month.
        if ((balance + interestThisMonth) <= MONTHLY_PAYMENT) {
            // This is the final payment. Takes the remaining balance plus interest to get the final payment amount.
            double principalPaid = balance;
            double finalPayment = balance + interestThisMonth;
            totalInterestPaid += interestThisMonth;
            balance = 0.0; // Loan is now fully paid off.

            cout << left
                 << setw(8) << month
                 << "$" << setw(11) << finalPayment
                 << "$" << setw(11) << interestThisMonth
                 << "$" << setw(11) << principalPaid
                 << "$" << balance << endl;
        } else {
            // This is a regular monthly payment. Calculate principal paid and update balance by subtracting principal paid.
            double principalPaid = MONTHLY_PAYMENT - interestThisMonth;
            balance -= principalPaid;
            totalInterestPaid += interestThisMonth;

            cout << left
                 << setw(8) << month
                 << "$" << setw(11) << MONTHLY_PAYMENT
                 << "$" << setw(11) << interestThisMonth
                 << "$" << setw(11) << principalPaid
                 << "$" << balance << endl;
        }
    }

    // Final Summary
    cout << "--------------------------------------------------------" << endl;
    cout << endl << "🎉 Loan paid off!" << endl;
    cout << "It took " << month << " months to repay the loan." << endl;
    cout << "Total interest paid: $" << totalInterestPaid << endl;

    return 0;
}