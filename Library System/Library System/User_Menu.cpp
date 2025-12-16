#include <iostream>
#include "MAIN.H"
#include "USERMENU.H"
#include "LIBRARY.H"
#include "BOOK.H"
using namespace std;

// Library object 

extern library lib;


void usermenu() {

    int userChoice;

    // User Menu

    do {


        cout << "\n===== User Menu =====\n";
        cout << "1. List Books\n";
        cout << "2. List Books by Category\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search Book\n";
        cout << "6. View Statistics\n";
        cout << "7. Logout\n";

        cout << "Enter your choice: ";
        cin >> userChoice;


        switch (userChoice) {


        case 1:

           lib.showAllBooks();
           break;


        case 2:

            lib.showBooksByCategory();
            break;


        case 3:

            lib.borrowBook();

            lib.saveBooksToFile ("books.txt");  // Auto-save
            break;


        case 4:

            lib.returnBook();

            lib.saveBooksToFile ("books.txt");  // Auto-save
            break;


        case 5:

            lib.searchBook();
            break;


        case 6:

            lib.showStatistics();
            break;


        case 7:

            lib.askSaveBeforeExit ("books.txt" , "books.csv");

            cout << "\nLogging out...\n";

            login(); //back to login section

            break;


        default:

            cout << "Invalid choice! Try again.\n";
        }


    } while (userChoice != 7);
}