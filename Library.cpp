#include "Library.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>

// Constructor implementation
Library::Library(const std::string& filename) : filename(filename) {
    loadFromFile();  // Load books when library is created
}

// Destructor ensures data persistence
Library::~Library() {
    saveToFile();  // Save books when library is destroyed
}

// Helper function to trim whitespace
std::string Library::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    
    if (start == std::string::npos || end == std::string::npos) {
        return "";
    }
    
    return str.substr(start, end - start + 1);
}

// Validate input to prevent malicious data
bool Library::validateStringInput(const std::string& str) const {
    if (str.empty()) return false;
    
    // Check for commas which would break CSV format
    if (str.find(',') != std::string::npos) return false;
    
    // Check length limits
    if (str.length() > 100) return false;
    
    return true;
}

// Find book by title (non-const version for modification)
Book* Library::findBookByTitle(const std::string& title) {
    std::string trimmedTitle = trim(title);
    
    for (auto& book : books) {
        if (trim(book.getTitle()) == trimmedTitle) {
            return &book;
        }
    }
    return nullptr;
}

// Find book by title (const version for read-only operations)
const Book* Library::findBookByTitle(const std::string& title) const {
    std::string trimmedTitle = trim(title);
    
    for (const auto& book : books) {
        if (trim(book.getTitle()) == trimmedTitle) {
            return &book;
        }
    }
    return nullptr;
}

// Load books from CSV file with error handling
bool Library::loadFromFile() {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "No existing data file found. Starting with empty library." << std::endl;
        return true;  // Not an error - first time running
    }
    
    std::string line;
    int lineCount = 0;
    int successCount = 0;
    
    while (std::getline(file, line)) {
        lineCount++;
        if (line.empty()) continue;
        
        try {
            Book book = Book::fromCSV(line);
            books.push_back(book);
            successCount++;
        } catch (const std::exception& e) {
            std::cout << "Warning: Skipping invalid line " << lineCount << ": " << line << std::endl;
        }
    }
    
    file.close();
    
    if (successCount > 0) {
        std::cout << "Successfully loaded " << successCount << " books from " << filename << std::endl;
    }
    
    return true;
}

// Save books to CSV file with error handling
bool Library::saveToFile() const {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing!" << std::endl;
        return false;
    }
    
    for (const auto& book : books) {
        file << book.toCSV() << std::endl;
        if (file.fail()) {
            std::cerr << "Error: Failed to write book data to file!" << std::endl;
            file.close();
            return false;
        }
    }
    
    file.close();
    std::cout << "Successfully saved " << books.size() << " books to " << filename << std::endl;
    return true;
}

// Add new book with validation
bool Library::addBook(const std::string& title, const std::string& author) {
    std::string trimmedTitle = trim(title);
    std::string trimmedAuthor = trim(author);
    
    // Input validation
    if (!validateStringInput(trimmedTitle) || !validateStringInput(trimmedAuthor)) {
        std::cout << "Error: Invalid input. Title and author must be non-empty, "
                  << "not contain commas, and be under 100 characters." << std::endl;
        return false;
    }
    
    // Check if book already exists
    if (findBookByTitle(trimmedTitle) != nullptr) {
        std::cout << "Error: Book \"" << trimmedTitle << "\" already exists in the library!" << std::endl;
        return false;
    }
    
    // Add the new book
    books.push_back(Book(trimmedTitle, trimmedAuthor, true));
    std::cout << "Successfully added \"" << trimmedTitle << "\" by " << trimmedAuthor << " to the library." << std::endl;
    return true;
}

// Lend a single book
bool Library::lendBook(const std::string& title) {
    std::string trimmedTitle = trim(title);
    Book* book = findBookByTitle(trimmedTitle);
    
    if (book == nullptr) {
        std::cout << "Error: Book \"" << trimmedTitle << "\" not found in the library!" << std::endl;
        return false;
    }
    
    if (book->borrowBook()) {
        std::cout << "Successfully lent \"" << trimmedTitle << "\"." << std::endl;
        return true;
    } else {
        std::cout << "Error: Book \"" << trimmedTitle << "\" is currently borrowed!" << std::endl;
        return false;
    }
}

// Return a single book
bool Library::returnBook(const std::string& title) {
    std::string trimmedTitle = trim(title);
    Book* book = findBookByTitle(trimmedTitle);
    
    if (book == nullptr) {
        std::cout << "Error: Book \"" << trimmedTitle << "\" not found in the library!" << std::endl;
        return false;
    }
    
    if (book->returnBook()) {
        std::cout << "Successfully returned \"" << trimmedTitle << "\"." << std::endl;
        return true;
    } else {
        std::cout << "Note: Book \"" << trimmedTitle << "\" was already available." << std::endl;
        return false;
    }
}

// Overloaded: Lend multiple books
int Library::lendBook(const std::vector<std::string>& titles) {
    int successCount = 0;
    
    for (const auto& title : titles) {
        if (lendBook(title)) {
            successCount++;
        }
    }
    
    std::cout << "Successfully lent " << successCount << " out of " << titles.size() << " books." << std::endl;
    return successCount;
}

// Overloaded: Return multiple books
int Library::returnBook(const std::vector<std::string>& titles) {
    int successCount = 0;
    
    for (const auto& title : titles) {
        if (returnBook(title)) {
            successCount++;
        }
    }
    
    std::cout << "Successfully returned " << successCount << " out of " << titles.size() << " books." << std::endl;
    return successCount;
}

// Display all available books
void Library::displayAvailableBooks() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "     AVAILABLE BOOKS IN LIBRARY" << std::endl;
    std::cout << "========================================" << std::endl;
    
    int availableCount = 0;
    
    for (const auto& book : books) {
        if (book.getAvailability()) {
            book.displayDetails();
            availableCount++;
        }
    }
    
    if (availableCount == 0) {
        std::cout << "No books are currently available." << std::endl;
    } else {
        std::cout << "\nTotal available books: " << availableCount << std::endl;
    }
    std::cout << "========================================\n" << std::endl;
}

// Get total book count
size_t Library::getBookCount() const {
    return books.size();
}

// Check if a book exists
bool Library::bookExists(const std::string& title) const {
    return findBookByTitle(title) != nullptr;
}