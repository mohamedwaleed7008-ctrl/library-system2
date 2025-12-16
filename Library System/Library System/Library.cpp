#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "LIBRARY.H"
#include "BOOK.H"

using namespace std;


// Library class


library::library() {};



// Function to load books from file

void library :: loadBooksFromFile (const string & filename) {

    ifstream inFile (filename);

    if (!inFile) {

        return;  // File doesn't exist, start fresh
    }

    books.clear();
    string line;

    while (getline (inFile, line)) {

        if (line.empty()) continue;

        istringstream iss(line);
        string token;
        Book book;

        try {

            getline (iss, token, '|');
            book.code = stoi(token);

            getline (iss, book.title, '|');
            getline (iss, book.author, '|');

            getline (iss, token, '|');
            book.Year = stoi(token);

            getline (iss, book.publisher, '|');
            getline (iss, book.category, '|');

            getline (iss, token, '|');
            book.isBorrowed = (token == "1");

            getline (iss, book.borrowedBy, '|');

            books.push_back(book);

        }
        catch (...) {
            // Skip invalid lines
        }
    }

    inFile.close();
}


// Function to save books to file

void library :: saveBooksToFile (const string & filename) {

    ofstream outFile (filename);

    if (!outFile) {

        cout << "❌ Error: Cannot save data to file!\n";
        return;
    }


    for (const auto & book : books) {

        outFile << book.code << "|"
            << book.title << "|"
            << book.author << "|"
            << book.Year << "|"
            << book.publisher << "|"
            << book.category << "|"
            << (book.isBorrowed ? "1" : "0") << "|"
            << book.borrowedBy << "\n";
    }

    outFile.close();
}


// Function to save books to CSV file

void library :: saveBooksToCSV (const string & filename) {

    ofstream csvFile (filename);

    if (!csvFile) {

        cout << "❌ Error: Cannot create CSV file '" << filename << "'\n";
        return;
    }


    // Write header (Titles)

    csvFile << "Code,Title,Author,Year,Publisher,Category,Status,Borrowed By\n";


    for (const auto & book : books) {

        // Replace commas in texts to avoid problems (CSV)

        string title = book.title;
        replace(title.begin(), title.end(), ',', ';');

        string author = book.author;
        replace(author.begin(), author.end(), ',', ';');

        string publisher = book.publisher;
        replace(publisher.begin(), publisher.end(), ',', ';');

        string category = book.category;
        replace(category.begin(), category.end(), ',', ';');

        string borrowedBy = book.borrowedBy;
        replace(borrowedBy.begin(), borrowedBy.end(), ',', ';');


        // Write data to CSV

        csvFile << book.code << ","
            << "\"" << title << "\","
            << "\"" << author << "\","
            << book.Year << ","
            << "\"" << publisher << "\","
            << "\"" << category << "\","
            << (book.isBorrowed ? "Borrowed" : "Available") << ","
            << "\"" << borrowedBy << "\"\n";
    }

    csvFile.close();
    cout << "📊 Saved " << books.size() << " books to CSV file: " << filename << "\n";
}


// Function to load books from CSV file

void library :: loadBooksFromCSV (const string & filename) {

    ifstream csvFile (filename);

    if (!csvFile) {

        cout << "📄 CSV file '" << filename << "' not found.\n";
        return;
    }

    books.clear();
    string line;
    int lineNumber = 0;
    int loadedCount = 0;


    // Skip header

    getline(csvFile, line);
    lineNumber++;


    while (getline (csvFile, line)) {

        lineNumber++;


        if (line.empty()) continue;

        istringstream iss (line);
        string token;
        Book book;

        try {

            // Read code

            getline (iss, token, ',');

            if (token.front() == '"') {

                token = token.substr(1, token.length() - 2);
            }

            book.code = stoi(token);


            // Read title (May contain commas)

            getline (iss, token, ',');

            if (token.front() == '"') {

                token = token.substr(1, token.length() - 2);

                replace (token.begin(), token.end(), ';', ',');
            }

            book.title = token;


            // Read author

            getline (iss, token, ',');

            if (token.front() == '"') {

                token = token.substr(1, token.length() - 2);

                replace(token.begin(), token.end(), ';', ',');
            }

            book.author = token;


            // Read year

            getline (iss, token, ',');

            book.Year = stoi(token);


            // Read publisher

            getline (iss, token, ',');

            if (token.front() == '"') {

                token = token.substr(1, token.length() - 2);

                replace(token.begin(), token.end(), ';', ',');
            }

            book.publisher = token;


            // Read category

            getline (iss, token, ',');

            if (token.front() == '"') {

                token = token.substr(1, token.length() - 2);

                replace(token.begin(), token.end(), ';', ',');
            }

            book.category = token;


            // Read status

            getline (iss, token, ',');

            book.isBorrowed = (token == "Borrowed");


            // Read borrowed by

            getline (iss, token, '\n');

            if (!token.empty() && token.front() == '"') {

                token = token.substr(1, token.length() - 2);

                replace(token.begin(), token.end(), ';', ',');
            }

            book.borrowedBy = token;

            books.push_back(book);
            loadedCount++;

        }

        catch (const exception& e) {

            cout << "⚠️ Warning: Error reading line " << lineNumber
                << " in CSV file: " << e.what() << "\n";
        }
    }

    csvFile.close();
    cout << "📂 Loaded " << loadedCount << " books from CSV file: " << filename << "\n";
}



// Function to add a new book to the collection

void library :: addBook () {

    Book newBook;

    cout << "\nEnter the code of the book: ";
    cin >> newBook.code;
    cin.ignore();


    cout << "Enter the title of the book: ";
    getline(cin, newBook.title);


    cout << "Enter the author of the book: ";
    getline(cin, newBook.author);


    cout << "Enter the publication year of the book: ";
    cin >> newBook.Year;
    cin.ignore();


    cout << "Enter the publisher of the book: ";
    getline(cin, newBook.publisher);


    cout << "Enter the category of the book: ";
    getline(cin, newBook.category);


    books.push_back(newBook);
    cout << "\n✅ Book added successfully!\n";
}



// Function to delete books

void library :: deleteBook () {

    int code;

    cout << "Enter book code to delete: ";
    cin >> code;

    bool found = false;


    for (auto it = books.begin(); it != books.end(); ++it) {

        if (it->code == code) {

            books.erase (it);

            cout << "✅ Book deleted successfully.\n";

            found = true;
            break;
        }
    }

    if (!found) {

        cout << "⚠️ Book not found.\n";
    }
}



// Function to search book

void library :: searchBook() {

    if (books.empty()) {

        cout << "\n⚠️ No books in the collection!\n";
        return;
    }


    int choice;

    cout << "\n===== Search Book =====\n";
    cout << "1. Search by Code\n";
    cout << "2. Search by Title\n";
    cout << "3. Search by category\n";
    cout << "0. Back to main menu\n";
    cout << "Choose: ";
    cin >> choice;
    cin.ignore();


    if (choice == 0) return;

    bool found = false;


    if (choice == 1) {

        int code;

        cout << "Enter book code: ";
        cin >> code;


        auto it = find_if (books.begin(), books.end(), [code] (const Book & book) {

                return book.code == code;

        });



        if (it != books.end()) {

            const Book& book = *it;

            cout << "\n✅ Book found:\n";
            cout << "Code: " << book.code << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Category: " << book.category << endl;
            cout << "Publication Year: " << book.Year << endl;
            cout << "Publisher: " << book.publisher << endl;

            if (book.isBorrowed)

                cout << "Status: Borrowed by " << book.borrowedBy << endl;

            else

                cout << "Status: Available\n";

            found = true;
        }
    }

    else if (choice == 2) {

        string title;

        cout << "Enter book title: ";
        getline (cin, title);


        for_each (books.begin(), books.end(), [&] (const Book & book) {

                if (book.title == title) {

                    cout << "\n✅ Book found:\n";
                    cout << "Code: " << book.code << endl;
                    cout << "Title: " << book.title << endl;
                    cout << "Author: " << book.author << endl;
                    cout << "Publication Year: " << book.Year << endl;
                    cout << "Publisher: " << book.publisher << endl;

                    if (book.isBorrowed)

                        cout << "Status: Borrowed by " << book.borrowedBy << endl;

                    else

                        cout << "Status: Available\n";

                    found = true;
                }

            });
    }

    else if (choice == 3) {

        string category;

        cout << "Enter book category: ";
        getline (cin, category);


        for_each (books.begin(), books.end(),[&] (const Book & book) {

                if (book.category == category) {

                    cout << "\n✅ Book found:\n";
                    cout << "Code: " << book.code << endl;
                    cout << "Title: " << book.title << endl;
                    cout << "Author: " << book.author << endl;
                    cout << "Category: " << book.category << endl;
                    cout << "Publication Year: " << book.Year << endl;
                    cout << "Publisher: " << book.publisher << endl;


                    if (book.isBorrowed)

                        cout << "Status: Borrowed by: " << book.borrowedBy << endl;

                    else

                        cout << "Status: Available\n";

                    found = true;
                }
            });
    }

    else {

        cout << "⚠️ Invalid choice!\n";
        return;
    }

    if (!found) 

        cout << "\n❌ No book found matching your search.\n";
    
}


// Function to borrow a book by code

void library :: borrowBook () {

    if (books.empty()) {

        cout << "\n⚠️ No books available to borrow!\n";
        return;
    }


    int code;

    cout << "Enter the code of the book to borrow: ";
    cin >> code;


    auto it = find_if (books.begin(), books.end(), [code] (Book & book) {

            return book.code == code;

        });


    if (it != books.end()) {

        if (it->isBorrowed) {

            cout << "\n❌ This book is already borrowed by " << it->borrowedBy << ".\n";
        }

        else {

            cout << "Enter borrower's name: ";
            cin.ignore();

            getline (cin, it->borrowedBy);

            it->isBorrowed = true;

            cout << "\n✅ Book borrowed successfully!\n";
        }

        return;
    }

    cout << "\n⚠️ Book not found.\n";
}



// Function to return a book by its title

void library :: returnBook () {

    if (books.empty()) {

        cout << "\n⚠️ No books in the collection!\n";
        return;
    }

    int code;

    cout << "Enter the code of the book to return: ";
    cin >> code;

    auto it = find_if (books.begin(), books.end(), [code](Book & book) {

            return book.code == code;
        });


    if (it != books.end()) {

        if (!it->isBorrowed) {

            cout << "\n❌ This book was not borrowed.\n";
        }


        else {

            it->isBorrowed = false;
            it->borrowedBy = "";
            cout << "\n✅ Book returned successfully!\n";
        }

        return;
    }

    cout << "\n⚠️ Book not found.\n";
}


// Function to show statistics

void library :: showStatistics () {

    if (books.empty()) {

        cout << "📊 Library is empty!\n";
        return;
    }

    map <string,int> categoryCount;
    int borrowed = 0;

    for_each(books.begin(), books.end(), [&](const Book & book) {

            categoryCount [book.category]++;

            if (book.isBorrowed)

                borrowed++;
        });


    cout << "\n📊 LIBRARY STATISTICS\n";
    cout << string (30, '=') << endl;
    cout << "Total Books: " << books.size() << endl;
    cout << "Borrowed: " << borrowed << endl;
    cout << "Available: " << books.size() - borrowed << endl;

    cout << "\n📚 Books by Category:\n";

    for (const auto& [category, count] : categoryCount) {

        cout << "  " << category << ": " << count << " books\n";
    }
}


// Function to ask user save before exit

void library :: askSaveBeforeExit (const string & dataFile, const string & csvFile) {

    char saveChoice;

    // Save to TXT

    cout << "\nSave data to TXT file before exiting? (y/n): ";
    cin >> saveChoice;


    if (tolower (saveChoice) == 'y') {

        saveBooksToFile (dataFile);
        cout << "✅ Data saved to TXT file!\n";
    }


    // Save to CSV

    cout << "\nExport to CSV file? (y/n): ";
    cin >> saveChoice;


    if (tolower (saveChoice) == 'y') {

        saveBooksToCSV (csvFile);
        cout << "✅ Data exported to CSV file!\n";
    }
}