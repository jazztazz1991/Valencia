/*
    Author: Cody Chase
    Date: 8/29/2025
    Unit 2 Program
    This program will demonstrate the concepts covered in chapter 2 of the textbook.
*/


#include <iostream>
using namespace std;

int main(){
    //First Part
    cout << "*****************************************" << endl;
    cout << "* Programming Assignment 1              *" << endl;
    cout << "* Computer Programming I                *" << endl;
    cout << "* Author: Your full name                *" << endl;
    cout << "* Due Date: Sunday, August 31, 2025     *" << endl;
    cout << "*****************************************" << endl << endl;

    // Second Part
    cout << "CCCCCCCCC" << "       " << "++" << "                 " << "++" << endl;
    cout << "CC" << "              " << "++" << "                 " << "++" << endl;
    cout << "CC" << "        " << "++++++++++++" << "        " << "++++++++++++" << endl;
    cout << "CC" << "        " << "++++++++++++" << "        " << "++++++++++++" << endl;
    cout << "CC" << "              " << "++" << "                 " << "++" << endl;
    cout << "CCCCCCCCC" << "       " << "++" << "                 " << "++" << endl;

    // Third Part
    int num1, num2, num3, average;

    num1 = 125;
    num2 = 28;
    num3 = -25;

    average = (num1 + num2 + num3) / 3;

    cout << "The values are:" << endl;
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
    cout << "num3 = " << num3 << endl;
    cout << "average = " << average << endl;

    // Fourth Part
    const double PI = 3.14;
    double radius, area, circumference;

    cout << "Enter the radius: ";
    cin >> radius;
    cout << endl;

    area = PI * radius * radius;
    circumference = 2 * PI * radius;

    cout << "Area = " << area << endl;
    cout << "Circumference = " << circumference << endl << endl;

    //Fifth Part
    string name;
    double studyHours;

    cout << "Enter your first name and hours you need to study: " << endl;
    cin >> name >> studyHours;
    cout << endl;

    cout << "Hello, " << name << "! On Saturday you need to study " << studyHours << " hours for the exam." << endl;

    double decimalNum;
    cout << "Enter a decimal number to be rounded: " << endl;
    cin >> decimalNum;
    cout << endl;

    int roundedValue = round(decimalNum);

    cout << "The rounded value is: " << roundedValue << endl;

    return 0;
} 