#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

int main(){
    // Open input and output files
    std::ifstream inFile;
    std::ofstream outFile;

    inFile.open("inData.txt");
    outFile.open("outData.txt");

    // Check if files opened successfully
    if (!inFile) {
        std::cerr << "Error opening inData.txt" << std::endl;
        return 1;
    }
    if (!outFile) {
        std::cerr << "Error opening outData.txt" << std::endl;
        return 1;
    }

    //declare variables
    std::string firstName, lastName, department;
    double salary, bonus, taxesPercent;
    double distance, travelTime;
    int coffeeCupSold;
    double coffeeCost;
    double bonusAmount, taxesAmount, payCheck, averageSpeed, salesAmount;

    // Read employee data
    inFile >> firstName >> lastName >> department;
    inFile >> salary >> bonus >> taxesPercent;
    inFile >> distance >> travelTime;
    inFile >> coffeeCupSold >> coffeeCost;
    // close input file to avoid accidental changes.
    inFile.close();

    // Calculations
    bonusAmount = salary * (bonus / 100);
    taxesAmount = (salary + bonusAmount) * (taxesPercent / 100);
    payCheck = salary + bonusAmount - taxesAmount;
    averageSpeed = distance / travelTime;
    salesAmount = coffeeCupSold * coffeeCost;

    
    // Output results to outData.txt
    outFile << "Name: " << firstName << " " << lastName << ", Department: " << department << std::endl;
    
    outFile << std::fixed << std::setprecision(2);
    outFile << "Monthly Gross Salary: $" << salary << ", Monthly Bonus: " << bonus << "%, Taxes: " << taxesPercent << "%" << std::endl;
    outFile << "Paycheck: $" << payCheck << std::endl;

    outFile << std::endl;

    outFile << "Distance Traveled: " << distance << " miles, Traveling Time: " << travelTime << " hours" << std::endl;
    outFile << "Average Speed: " << std::setprecision(2) << averageSpeed << " miles per hour" << std::endl;

    outFile << std::endl;

    outFile << "Coffee Cups Sold: " << coffeeCupSold << ", Cost per Cup: $" << coffeeCost << std::endl;
    outFile << "Total Sales Amount: $" << salesAmount << std::endl;

    // Close output file
    outFile.close();
    return 0;
}