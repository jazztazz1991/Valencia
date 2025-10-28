/*
    Author: Cody Chase
    Date: 10/27/2025
    Unit 10 Program
    A menu-driven C++ application that manages a book inventory and includes a Roman numeral converter.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>
#include <cctype>

// Forward declaration of classes
class bookType;
class romanType;

// Function prototypes
void displayMenu();
void loadBooks(std::vector<bookType>& books, const std::string& filename);
void displayAllBooks(const std::vector<bookType>& books);
void searchByTitle(const std::vector<bookType>& books);
void searchByISBN(const std::vector<bookType>& books);
void updateStock(std::vector<bookType>& books);
void convertRomanNumeral();
void printBookDetails(const bookType& book);
void saveBooks(const std::vector<bookType>& books, const std::string& filename);

class bookType {
private:
    std::string title;
    std::vector<std::string> authors;
    std::string publisher;
    std::string isbn;
    double price;
    int stock;

public:
    // Setters
    void setTitle(const std::string& t) { title = t; }
    void setAuthors(const std::vector<std::string>& a) { authors = a; }
    void setPublisher(const std::string& p) { publisher = p; }
    void setISBN(const std::string& i) { isbn = i; }
    void setPrice(double p) { price = p; }
    void setStock(int s) { stock = s; }

    // Getters
    std::string getTitle() const { return title; }
    std::vector<std::string> getAuthors() const { return authors; }
    std::string getPublisher() const { return publisher; }
    std::string getISBN() const { return isbn; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
};

class romanType {
private:
    std::string romanNumeral;
    int integerValue;
    std::map<char, int> romanMap;

    void convertToInteger() {
        integerValue = 0;
        if (romanNumeral.empty()) return;

        for (size_t i = 0; i < romanNumeral.length(); ++i) {
            if (romanMap.find(romanNumeral[i]) == romanMap.end()) {
                integerValue = -1; // Invalid character
                return;
            }
            if (i + 1 < romanNumeral.length() && romanMap[romanNumeral[i]] < romanMap[romanNumeral[i + 1]]) {
                integerValue -= romanMap[romanNumeral[i]];
            } else {
                integerValue += romanMap[romanNumeral[i]];
            }
        }
    }

public:
    romanType(const std::string& roman) : romanNumeral(roman) {
        romanMap['I'] = 1;
        romanMap['V'] = 5;
        romanMap['X'] = 10;
        romanMap['L'] = 50;
        romanMap['C'] = 100;
        romanMap['D'] = 500;
        romanMap['M'] = 1000;
        convertToInteger();
    }

    void print() const {
        std::cout << "Roman Numeral: " << romanNumeral << std::endl;
        if (integerValue != -1) {
            std::cout << "Integer Value: " << integerValue << std::endl;
        } else {
            std::cout << "Invalid Roman numeral." << std::endl;
        }
    }
};

int main() {
    std::vector<bookType> books;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Consume the newline character

        switch (choice) {
            case 1:
                loadBooks(books, "books.txt");
                displayAllBooks(books);
                break;
            case 2:
                loadBooks(books, "books.txt");
                searchByTitle(books);
                break;
            case 3:
                loadBooks(books, "books.txt");
                searchByISBN(books);
                break;
            case 4:
                loadBooks(books, "books.txt");
                updateStock(books);
                break;
            case 5:
                convertRomanNumeral();
                break;
            case 6:
                std::cout << "Thank you for using this program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        std::cout << std::endl;
    } while (choice != 6);

    return 0;
}

void displayMenu() {
    std::cout << "Menu Options:" << std::endl;
    std::cout << "1: Display All Books" << std::endl;
    std::cout << "2: Search for a Book by Title" << std::endl;
    std::cout << "3: Search for a Book by ISBN" << std::endl;
    std::cout << "4: Update Number of Copies in Stock" << std::endl;
    std::cout << "5: Roman Numeral Conversion" << std::endl;
    std::cout << "6: Exit the Program" << std::endl;
    std::cout << "Enter your choice: ";
}

void loadBooks(std::vector<bookType>& books, const std::string& filename) {
    books.clear();
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        bookType newBook;
        newBook.setTitle(line);

        int numAuthors;
        inFile >> numAuthors;
        inFile.ignore(); 

        std::vector<std::string> authors;
        for (int i = 0; i < numAuthors; ++i) {
            std::getline(inFile, line);
            authors.push_back(line);
        }
        newBook.setAuthors(authors);

        std::getline(inFile, line);
        newBook.setPublisher(line);

        std::getline(inFile, line);
        newBook.setISBN(line);

        double price;
        inFile >> price;
        newBook.setPrice(price);

        int stock;
        inFile >> stock;
        inFile.ignore();
        newBook.setStock(stock);

        books.push_back(newBook);
    }
    inFile.close();
}

void saveBooks(const std::vector<bookType>& books, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < books.size(); ++i) {
        const auto& book = books[i];
        outFile << book.getTitle() << std::endl;
        outFile << book.getAuthors().size() << std::endl;
        for (const auto& author : book.getAuthors()) {
            outFile << author << std::endl;
        }
        outFile << book.getPublisher() << std::endl;
        outFile << book.getISBN() << std::endl;
        outFile << book.getPrice() << std::endl;
        outFile << book.getStock();
        if (i < books.size() - 1) {
            outFile << std::endl;
        }
    }
    outFile.close();
}

void printBookDetails(const bookType& book) {
    std::cout << "Title: " << book.getTitle() << std::endl;
    std::cout << "Authors: ";
    const auto& authors = book.getAuthors();
    for (size_t i = 0; i < authors.size(); ++i) {
        std::cout << authors[i] << (i == authors.size() - 1 ? "" : ", ");
    }
    std::cout << std::endl;
    std::cout << "Publisher: " << book.getPublisher() << std::endl;
    std::cout << "ISBN: " << book.getISBN() << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Price: $" << book.getPrice() << std::endl;
    std::cout << "Copies in Stock: " << book.getStock() << std::endl;
}

void displayAllBooks(const std::vector<bookType>& books) {
    if (books.empty()) {
        std::cout << "No books to display." << std::endl;
        return;
    }
    for (const auto& book : books) {
        printBookDetails(book);
        std::cout << std::endl;
    }
}

void searchByTitle(const std::vector<bookType>& books) {
    std::cout << "Enter title to search: ";
    std::string title;
    std::getline(std::cin, title);

    bool found = false;
    for (const auto& book : books) {
        if (book.getTitle() == title) {
            printBookDetails(book);
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Book not found." << std::endl;
    }
}

void searchByISBN(const std::vector<bookType>& books) {
    std::cout << "Enter ISBN to search: ";
    std::string isbn;
    std::getline(std::cin, isbn);

    bool found = false;
    for (const auto& book : books) {
        if (book.getISBN() == isbn) {
            printBookDetails(book);
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Book not found." << std::endl;
    }
}

void updateStock(std::vector<bookType>& books) {
    std::cout << "Enter title of book to update: ";
    std::string title;
    std::getline(std::cin, title);

    bookType* bookToUpdate = nullptr;
    for (auto& book : books) {
        if (book.getTitle() == title) {
            bookToUpdate = &book;
            break;
        }
    }

    if (bookToUpdate) {
        std::cout << "Enter number of copies to add (use negative number to subtract): ";
        int change;
        std::cin >> change;
        std::cin.ignore();

        bookToUpdate->setStock(bookToUpdate->getStock() + change);

        std::cout << "Updated book info:" << std::endl;
        printBookDetails(*bookToUpdate);

        saveBooks(books, "books.txt");
        std::cout << "Inventory has been updated." << std::endl;
    } else {
        std::cout << "Book not found." << std::endl;
    }
}

void convertRomanNumeral() {
    std::cout << "Enter a Roman numeral: ";
    std::string roman;
    std::getline(std::cin, roman);

    // Convert to uppercase
    std::transform(roman.begin(), roman.end(), roman.begin(),
                   [](unsigned char c){ return std::toupper(c); });

    romanType romanConverter(roman);
    romanConverter.print();
}
