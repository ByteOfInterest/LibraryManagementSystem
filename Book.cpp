#include "Book.h"
#include <sstream>
#include <iomanip>

// Constructor implementation
Book::Book(const std::string& title, const std::string& author, bool available)
    : title(title), author(author), isAvailable(available) {
    // Using initializer list for efficient initialization
}

// Copy constructor - performs deep copy
Book::Book(const Book& other) 
    : title(other.title), author(other.author), isAvailable(other.isAvailable) {
    // No dynamic memory to manage, but implementing for completeness
}

// Destructor - nothing to clean up since we use std::string
Book::~Book() {
    // No dynamic memory allocation to free
}

// Assignment operator implementation
Book& Book::operator=(const Book& other) {
    if (this != &other) {  // Self-assignment check
        title = other.title;
        author = other.author;
        isAvailable = other.isAvailable;
    }
    return *this;
}

// Getter implementations
std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

bool Book::getAvailability() const {
    return isAvailable;
}

// Setter implementations
void Book::setTitle(const std::string& title) {
    this->title = title;
}

void Book::setAuthor(const std::string& author) {
    this->author = author;
}

void Book::setAvailability(bool available) {
    this->isAvailable = available;
}

// Display book details with proper formatting
void Book::displayDetails() const {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Title:  " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Status: " << (isAvailable ? "Available" : "Borrowed") << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

// Borrow book logic
bool Book::borrowBook() {
    if (isAvailable) {
        isAvailable = false;
        return true;
    }
    return false;
}

// Return book logic
bool Book::returnBook() {
    if (!isAvailable) {
        isAvailable = true;
        return true;
    }
    return false;
}

// Convert to CSV format for file storage
std::string Book::toCSV() const {
    return title + "," + author + "," + (isAvailable ? "1" : "0");
}

// Static method to create Book from CSV line
Book Book::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string title, author, status;
    
    std::getline(ss, title, ',');
    std::getline(ss, author, ',');
    std::getline(ss, status, ',');
    
    bool isAvailable = (status == "1");
    
    return Book(title, author, isAvailable);
}