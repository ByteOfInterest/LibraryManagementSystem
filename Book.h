#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

/**
 * @class Book
 * @brief Represents a single book in the library system
 * 
 * This class encapsulates all attributes and behaviors of a book,
 * following encapsulation principles of OOP.
 */
class Book {
private:
    std::string title;      ///< Title of the book
    std::string author;     ///< Author of the book
    bool isAvailable;       ///< Availability status (true = available, false = borrowed)

public:
    /**
     * @brief Constructor with parameters
     * @param title The book's title
     * @param author The book's author
     * @param available Initial availability status (default: true)
     */
    Book(const std::string& title = "", const std::string& author = "", bool available = true);
    
    /**
     * @brief Copy constructor for deep copying
     * @param other The book to copy from
     */
    Book(const Book& other);
    
    /**
     * @brief Destructor
     */
    ~Book();
    
    /**
     * @brief Assignment operator overload
     * @param other The book to assign from
     * @return Reference to this book
     */
    Book& operator=(const Book& other);
    
    // Getters
    std::string getTitle() const;
    std::string getAuthor() const;
    bool getAvailability() const;
    
    // Setters
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setAvailability(bool available);
    
    /**
     * @brief Displays all book details in a formatted manner
     */
    void displayDetails() const;
    
    /**
     * @brief Attempts to borrow the book
     * @return true if successful, false if book is already borrowed
     */
    bool borrowBook();
    
    /**
     * @brief Returns the book to the library
     * @return true if successful, false if book was already available
     */
    bool returnBook();
    
    /**
     * @brief Converts book data to CSV format for file storage
     * @return CSV formatted string
     */
    std::string toCSV() const;
    
    /**
     * @brief Creates a Book object from CSV format
     * @param csvLine CSV formatted string
     * @return Book object created from CSV data
     */
    static Book fromCSV(const std::string& csvLine);
};

#endif 