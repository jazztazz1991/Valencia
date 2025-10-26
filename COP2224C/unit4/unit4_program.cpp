/*
    Author: Cody Chase
    Date: 9/14/2025
    Unit 4 Program
    Hotel Room Discount Calculator
        - Prompts for cost per room, number of rooms, number of days, and sales tax percent
        - Discounts:
            * 10% for 10-19 rooms
            * 20% for 20-29 rooms
            * 30% for 30+ rooms
            * Extra 5% if booked for at least 3 days
*/

#include <iostream>
#include <iomanip>
using namespace std;

// Named constants for discounts
const double DISCOUNT_10 = 0.10;
const double DISCOUNT_20 = 0.20;
const double DISCOUNT_30 = 0.30;
const double EXTRA_DISCOUNT_DAYS = 0.05;
const int MIN_ROOMS_10 = 10;
const int MIN_ROOMS_20 = 20;
const int MIN_ROOMS_30 = 30;
const int MIN_DAYS_EXTRA = 3;

int main() {
	double roomRate, salesTaxPercent;
	int numRooms, numDays;
	double discount = 0.0;

	// Get the users input
	cout << "Enter the cost of renting one room: $";
	cin >> roomRate;
	cout << "Enter the number of rooms to book: ";
	cin >> numRooms;
	cout << "Enter the number of days to book: ";
	cin >> numDays;
	cout << "Enter the sales tax (as a percent): ";
	cin >> salesTaxPercent;

	// Calculate discount based on number of rooms
	if (numRooms >= MIN_ROOMS_30) {
		discount = DISCOUNT_30;
	} else if (numRooms >= MIN_ROOMS_20) {
		discount = DISCOUNT_20;
	} else if (numRooms >= MIN_ROOMS_10) {
		discount = DISCOUNT_10;
	}

	// Check for extra discount based on number of days
	if (numDays >= MIN_DAYS_EXTRA) {
		discount += EXTRA_DISCOUNT_DAYS;
	}

	double totalCost = numRooms * numDays * roomRate;
	double discountAmount = totalCost * discount;
	double discountedTotal = totalCost - discountAmount;
	double salesTax = discountedTotal * (salesTaxPercent / 100.0);
	double finalBilling = discountedTotal + salesTax;

	// Output results
	cout << fixed << setprecision(2);
	cout << "\nCost of renting one room: $" << roomRate << endl;
	cout << "Discount on each room: " << (discount * 100) << "%" << endl;
	cout << "Number of rooms booked: " << numRooms << endl;
	cout << "Number of days booked: " << numDays << endl;
	cout << "Total cost of rooms (before discount): $" << totalCost << endl;
	cout << "Sales tax: $" << salesTax << endl;
	cout << "Total billing amount: $" << finalBilling << endl;

	return 0;
}
