#include <iostream>
#include "MAIN.H"
#include "ADMINMENU.H"
#include "LIBRARY.H"
#include "BOOK.H"
using namespace std;

// Library object

extern library lib;


void adminmenu() {


    int adminChoice;

    //Admin Menu

    do {

        cout << "\n===== Admin Menu =====\n";
        cout << "1. Add new book\n";
        cout << "2. Delete book\n";
        cout << "3. List books\n";
        cout << "4. List Books by Category\n";
        cout << "5. View Statistics\n";
        cout << "6. Save Data (TXT)\n";
        cout << "7. Export to CSV\n";
        cout << "8. Import from CSV\n";
        cout << "9. Logout\n";


        cout << "Enter your choice: ";
        cin >> adminChoice;


        //Check Choice

        switch (adminChoice) {

        case 1:


            lib.addBook();

            lib.saveBooksToFile("books.txt");  // Auto-save
            break;


        case 2:


            lib.deleteBook();

            lib.saveBooksToFile("books.txt");  // Auto-save
            break;


        case 3:

            lib.showAllBooks();
            break;


        case 4:


            lib.showBooksByCategory();
            break;


        case 5:

            lib.showStatistics();
            break;


        case 6:

            lib.saveBooksToFile("books.txt");

            cout << "✅ Data saved to TXT file!\n";
            break;


        case 7:

            lib.saveBooksToCSV("books.csv");
            break;


        case 8:
        {
            string filename;

            cout << "Enter CSV filename to import: ";
            cin.ignore();

            getline (cin, filename);

            lib.loadBooksFromCSV(filename);

            lib.saveBooksToFile("books.txt"); // Save to regular format

            cout << "✅ Data imported from CSV!\n";
            break;
        }



        case 9:
        {

            lib.askSaveBeforeExit("books.txt" , "books.csv");

            cout << "\nLogging out...\n";

            login(); //back to login section

            break;
        }

        default:
        
            cout << "Invalid choice! Try again.\n";
        }

        } while (adminChoice != 9);

    }