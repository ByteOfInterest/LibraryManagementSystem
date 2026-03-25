#include "Library.h"
#include <iostream>
#include <limits>
#include <sstream>

/**
 * @brief Displays the main menu options
 */
void displayMenu() {
    std::cout << "\n╔════════════════════════════════════╗" << std::endl;
    std::cout << "║     LIBRARY MANAGEMENT SYSTEM      ║" << std::endl;
    std::cout << "╠════════════════════════════════════╣" << std::endl;
    std::cout << "║  1. Add a New Book                 ║" << std::endl;
    std::cout << "║  2. Lend Book(s)                   ║" << std::endl;
    std::cout << "║  3. Return Book(s)                 ║" << std::endl;
    std::cout << "║  4. View Available Books           ║" << std::endl;
    std::cout << "║  5. Exit                           ║" << std::endl;
    std::cout << "╚════════════════════════════════════╝" << std::endl;
    std::cout << "Enter your choice (1-5): ";
}

/**
 * @brief Clears input buffer to prevent issues with getline
 */
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Gets a valid integer input from user
 * @param min Minimum allowed value
 * @param max Maximum allowed value
 * @return Valid integer input
 */
int getValidatedIntInput(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Invalid input! Please enter a number (" << min << "-" << max << "): ";
        } else if (choice < min || choice > max) {
            std::cout << "Invalid choice! Please enter " << min << "-" << max << ": ";
        } else {
            clearInputBuffer();
            return choice;
        }
    }
}

/**
 * @brief Gets a non-empty string input from user
 * @param prompt Message to display
 * @return Validated string input
 */
std::string getValidatedString(const std::string& prompt) {
    std::string input;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        // Remove leading/trailing spaces
        size_t start = input.find_first_not_of(" \t");
        if (start != std::string::npos) {
            input = input.substr(start);
        }
        
        size_t end = input.find_last_not_of(" \t");
        if (end != std::string::npos) {
            input = input.substr(0, end + 1);
        }
        
        if (!input.empty()) {
            return input;
        }
        
        std::cout << "Input cannot be empty! Please try again." << std::endl;
    }
}

/**
 * @brief Parses comma-separated titles from user input
 * @param input Raw input string
 * @return Vector of trimmed titles
 */
std::vector<std::string> parseTitles(const std::string& input) {
    std::vector<std::string> titles;
    std::stringstream ss(input);
    std::string title;
    
    while (std::getline(ss, title, ',')) {
        // Trim whitespace
        size_t start = title.find_first_not_of(" \t");
        size_t end = title.find_last_not_of(" \t");
        
        if (start != std::string::npos && end != std::string::npos) {
            title = title.substr(start, end - start + 1);
            if (!title.empty()) {
                titles.push_back(title);
            }
        }
    }
    
    return titles;
}

/**
 * @brief Handles the add book operation
 * @param library Reference to Library object
 */
void handleAddBook(Library& library) {
    std::cout << "\n--- ADD NEW BOOK ---" << std::endl;
    std::string title = getValidatedString("Enter book title: ");
    std::string author = getValidatedString("Enter author name: ");
    
    library.addBook(title, author);
}

/**
 * @brief Handles the lend books operation
 * @param library Reference to Library object
 */
void handleLendBooks(Library& library) {
    std::cout << "\n--- LEND BOOKS ---" << std::endl;
    std::cout << "Do you want to lend (1) one book or (2) multiple books? ";
    
    int choice = getValidatedIntInput(1, 2);
    
    if (choice == 1) {
        std::string title = getValidatedString("Enter book title: ");
        library.lendBook(title);
    } else {
        std::cout << "Enter book titles separated by commas (e.g., The Hobbit, 1984, Dune): ";
        std::string input;
        std::getline(std::cin, input);
        
        std::vector<std::string> titles = parseTitles(input);
        
        if (titles.empty()) {
            std::cout << "No valid titles entered!" << std::endl;
        } else {
            library.lendBook(titles);
        }
    }
}

/**
 * @brief Handles the return books operation
 * @param library Reference to Library object
 */
void handleReturnBooks(Library& library) {
    std::cout << "\n--- RETURN BOOKS ---" << std::endl;
    std::cout << "Do you want to return (1) one book or (2) multiple books? ";
    
    int choice = getValidatedIntInput(1, 2);
    
    if (choice == 1) {
        std::string title = getValidatedString("Enter book title: ");
        library.returnBook(title);
    } else {
        std::cout << "Enter book titles separated by commas (e.g., The Hobbit, 1984, Dune): ";
        std::string input;
        std::getline(std::cin, input);
        
        std::vector<std::string> titles = parseTitles(input);
        
        if (titles.empty()) {
            std::cout << "No valid titles entered!" << std::endl;
        } else {
            library.returnBook(titles);
        }
    }
}

/**
 * @brief Main program entry point
 */
int main() {
    std::cout << "╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║     WELCOME TO THE LIBRARY MANAGEMENT SYSTEM          ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    
    // Create library instance (automatically loads from file)
    Library library("books.csv");
    
    std::cout << "\nLibrary initialized with " << library.getBookCount() << " books." << std::endl;
    
    bool running = true;
    
    while (running) {
        displayMenu();
        
        int choice = getValidatedIntInput(1, 5);
        
        switch (choice) {
            case 1:
                handleAddBook(library);
                break;
                
            case 2:
                handleLendBooks(library);
                break;
                
            case 3:
                handleReturnBooks(library);
                break;
                
            case 4:
                library.displayAvailableBooks();
                break;
                
            case 5:
                std::cout << "\nSaving library data..." << std::endl;
                // Library destructor will save automatically
                std::cout << "Thank you for using the Library Management System!" << std::endl;
                std::cout << "Goodbye!" << std::endl;
                running = false;
                break;
        }
    }
    
    return 0;
}