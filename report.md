Project Report

Author: Anastasiia Zhelizniak

1. What I Built

So for this project, I made a Library Management System in C++. It's a program that helps you keep track of books. You can add new books, lend them out, return them, and see which ones are available. The program saves everything to a file so when you close it and open it again later, all your books are still there.

I tried to make it user-friendly with a simple menu system and good error messages so people don't get confused when they type something wrong.

2. How I Used Object-Oriented Programming

    2.1 Keeping Things Hidden (Encapsulation)

    One thing, is keeping data private and only letting people change it through specific functions. I did that here. In my Book class, things like the title, author, and whether it's available are all private. You can't just go in and change them directly. If you want to borrow a book, you have to call borrowBook(), which checks if it's available first. This way, nobody can accidentally break things by setting a book as borrowed when it's already taken or something like that.

    2.2 Making Things Simple (Abstraction)

    The Library class hides all the complicated stuff from whoever is using it. When someone uses my program, they just see simple options like "add book" or "lend book." They don't need to know that behind the scenes, I'm working with vectors, reading from CSV files, or searching through lists. This makes the main program much cleaner and easier to understand.

    2.3 Planning for the Future

    Right now, I only have a basic Book class, but I designed it so that if I wanted to add special types of books later (like e-books or audiobooks), I could make them as subclasses without having to rewrite everything. That's one of the cool things about OOP.

    2.4 Handling Memory Properly

    I used std::vector to store my books, which automatically handles memory allocation for me. I didn't want to mess around with manual memory management and risk memory leaks. The only time I use pointers is in the findBookByTitle() method, where I return a pointer to a book if I find it. This way I don't have to copy the whole book object when I'm just looking for it.

3. How Everything Works

    3.1 Saving and Loading Data

    When the program starts up, it automatically looks for a file called "books.csv" and loads any books it finds. When you exit, it saves everything back. I used CSV format because it's simple and easy to read. If the file doesn't exist when you first run it, the program just starts with an empty library and creates the file later. I also added error handling so if a line in the file is messed up, it skips it instead of crashing.

    3.2 Checking User Input

    I spent a lot of time making sure the program doesn't break when people type weird stuff. Here's what I check for:

    Menu choices have to be numbers between 1 and 5;
    Book titles and authors can't be empty;
    You can't have commas in titles or authors (since I use commas to separate things in the file);
    Before lending a book, I make sure it exists AND it's available;
    Before returning, I make sure it exists;

    3.3 Lending and Returning Multiple Books

    One of the requirements was to have overloaded functions for lending/returning multiple books at once. So I made two versions of lendBook(), one that takes a single title, and another that takes a list of titles. The program asks users if they want to lend one book or multiple, and then handles it accordingly.

4. Making the Code Clean

    4.1 Comments Everywhere

    I wrote comments for all my classes and functions. Not just what they do, but also what parameters they take and what they return. This makes it easier for someone else to understand my code (or for me to remember what I was thinking when I come back to it later).

    4.2 Handling Errors Gracefully

    Instead of just letting the program crash when something goes wrong, I try to catch errors and show helpful messages. For example, if someone tries to lend a book that doesn't exist, the program tells them "Book not found" instead of just doing nothing or crashing. Same thing if the file can't be saved. It prints an error message so the user knows something went wrong.

    4.3 Keeping Things Organized

    I split my code into separate files: .h files for declarations and .cpp files for implementations. This is pretty standard in C++ and makes the code easier to manage. The main.cpp file is just for the menu loop. All the actual work is in the other files.

5. Testing What I Made

I tested the program with a bunch of different scenarios to make sure it works:

Adding duplicate books: Tried adding the same book twice, program correctly said it already exists;

Lending unavailable books: Tried lending a book that was already borrowed, program said it wasn't available;

Returning books that don't exist: Tried returning a random book that wasn't in the system, program said it wasn't found;

Corrupted files: Made a CSV file with some bad lines, program loaded the good ones and skipped the bad ones;

Multiple books in one go: Lent and returned several books at once using commas, it processed all of them;

Weird inputs: Tried entering spaces, empty strings, and letters when numbers were expected. Program handled it all without crashing;

Everything worked as expected, which was pretty satisfying to see.

6. What I Learned

This project taught me a lot about how to structure a C++ program properly. I got to practice using classes, vectors, file I/O, and error handling all together. It's one thing to learn these concepts separately, but putting them all into one working project is different. I also learned that spending time on input validation upfront saves a lot of headaches later when people try to break your program.

7. Things I'd Add If I Had More Time

If I kept working on this, here's what I'd add:

Due dates, so you can track when books need to be returned;

Search by author, right now you can only search by exact title;

Better search, being able to search by partial titles would be nice;

User accounts, so librarians and regular users have different permissions;

Late fees, because libraries always have those;

Graphical interface, a real window with buttons would look more professional;

8. Final Thoughts

Overall, I'm pretty happy with how this turned out. The program does everything it was supposed to do, it handles errors well, and it's organized in a way that makes sense. The code follows the OOP principles, and it should be easy to add new features later if I want to. Getting all the little details right took some time, but it was worth it to have a solid program that doesn't crash when users do something unexpected.

