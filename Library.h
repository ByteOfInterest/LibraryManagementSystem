#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Book.h"

/**
 * @class Library
 * @brief Manages a collection of books in the library system
 * 
 * This class provides all core functionality for book management,
 * demonstrating encapsulation and abstraction principles.
 */
class Library {
private:
    std::vector<Book> books;  ///< Collection of books using STL vector for dynamic management
    std::string filename;     ///< File path for persistent storage
    
    /**
     * @brief Finds a book by its title
     * @param title The title to search for
     * @return Pointer to the book if found, nullptr otherwise
     */
    Book* findBookByTitle(const std::string& title);
    
    /**
     * @brief Finds a book by its title (const version)
     * @param title The title to search for
     * @return Const pointer to the book if found, nullptr otherwise
     */
    const Book* findBookByTitle(const std::string& title) const;
    
    /**
     * @brief Validates if a string contains only valid characters
     * @param str The string to validate
     * @return true if valid, false otherwise
     */
    bool validateStringInput(const std::string& str) const;
    
    /**
     * @brief Trim whitespace from beginning and end of string
     * @param str The string to trim
     * @return Trimmed string
     */
    std::string trim(const std::string& str) const;

public:
    /**
     * @brief Constructor
     * @param filename File path for book data storage
     */
    explicit Library(const std::string& filename = "books.csv");
    
    /**
     * @brief Destructor - ensures data is saved
     */
    ~Library();
    
    /**
     * @brief Loads book data from file
     * @return true if successful, false otherwise
     */
    bool loadFromFile();
    
    /**
     * @brief Saves book data to file
     * @return true if successful, false otherwise
     */
    bool saveToFile() const;
    
    /**
     * @brief Adds a new book to the library
     * @param title Book title
     * @param author Book author
     * @return true if successful, false if book already exists
     */
    bool addBook(const std::string& title, const std::string& author);
    
    /**
     * @brief Lends a single book
     * @param title Book title to lend
     * @return true if successful, false otherwise
     */
    bool lendBook(const std::string& title);
    
    /**
     * @brief Returns a single book
     * @param title Book title to return
     * @return true if successful, false otherwise
     */
    bool returnBook(const std::string& title);
    
    /**
     * @brief Overloaded function to lend multiple books
     * @param titles Vector of book titles to lend
     * @return Number of books successfully lent
     */
    int lendBook(const std::vector<std::string>& titles);
    
    /**
     * @brief Overloaded function to return multiple books
     * @param titles Vector of book titles to return
     * @return Number of books successfully returned
     */
    int returnBook(const std::vector<std::string>& titles);
    
    /**
     * @brief Displays all available books in the library
     */
    void displayAvailableBooks() const;
    
    /**
     * @brief Gets the total number of books in the library
     * @return Number of books
     */
    size_t getBookCount() const;
    
    /**
     * @brief Checks if a book exists in the library
     * @param title Book title to check
     * @return true if exists, false otherwise
     */
    bool bookExists(const std::string& title) const;
};

#endif // LIBRARY_H