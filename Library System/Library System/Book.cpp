#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "BOOK.H"
using namespace std;


// Function to list all the books

void listBooks (const vector <Book> & books) { 

    cout << "\n===== Book Collection =====\n";

    for (const auto& book : books) {

        cout << "Code: " << book.code << endl;
        cout << "Title: " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "Category: " << book.category << endl;
        cout << "Publication Year: " << book.Year << endl;
        cout << "Publisher: " << book.publisher << endl;


        if (book.isBorrowed)

            cout << "Status: Borrowed by " << book.borrowedBy << endl;

        else

            cout << "Status: Available" << endl;

        cout << "--------------------------\n";
    }
}


// Function to list books by category

void listBooksByCategory (const vector <Book> & books) { 


    // Get all unique categories

    vector<string> categories;

    for (const auto& book : books) {

        if (find(categories.begin(), categories.end(), book.category) == categories.end()) {

            categories.push_back(book.category);
        }
    }

    cout << "\n===== Categories =====\n";

    for (int i = 0; i < categories.size(); i++) {

        cout << i + 1 << ". " << categories[i] << endl;
    }

    int choice;

    cout << "Choose category (0 to go back): ";
    cin >> choice;

    if (choice == 0) return;

    if (choice < 1 || choice > categories.size()) {

        cout << "Invalid choice!\n";
        return;
    }

    string selectedCategory = categories[choice - 1];

    cout << "\n===== Books in " << selectedCategory << " =====\n";

    bool found = false;

    for (const auto& book : books) {

        if (book.category == selectedCategory) {

            cout << "Code: " << book.code << " | Title: " << book.title;
            cout << " | Author: " << book.author;

            if (book.isBorrowed)

                cout << " | Status: Borrowed by " << book.borrowedBy << endl;

            else

                cout << " | Status: Available" << endl;

            found = true;
        }
    }

    if (!found) {

        cout << "No books found in this category.\n";
    }
}



// Function to initialize Books with categories

void initializeBooks(vector <Book> & books) {

    books.clear();


    Book book1(

        Book(100, "Python", "Python Crash Course", "Eric Matthes", 2023, "Eric Matthes")

    );

  

    Book book2(

        Book (101, "Python", "Core Python Programming", "Wesley J. Chun", 2006, "Wesley J. Chun")

    );

    
    Book book3(

        Book(102, "C++", "The C++ Programming Language", "Wesley J. Chun", 2006, "Wesley J. Chun")

    );


    book3.isBorrowed = true;
    book3.borrowedBy = "Mohamed";

    books.push_back(book3);



    Book book4(

        Book (103 , "Java" , "Effective Java" , "Joshua Bloch" , 2008 , "Addison Wesley")

    );

    book4.isBorrowed = true;
    book4.borrowedBy = "Ahmed";

    books.push_back(book4);


    Book book5(

        Book (104 , "C++" , "Effective Modern C++" , "Scott Meyers" , 2014 , "O'Reilly Media")

    );


    Book book6(

        Book(105 , "C++", "A Tour of C++", "Bjarne Stroustrup", 2022, "Addison-Wesley Professional")

    );
    

    Book book7(

        Book(106 , "Java" , "Head First Java" , "Kathy Sierra , Bert Bates" , 2005 , "O'Reilly Media")

    );


    Book book8(

        Book(107 , "Java" , "Core Java Volume" , "Cay S. Horstmann" , 2021 , "Prentice Hall")

    );


    Book book9(

        Book(108 , "Python" , "Fluent Python" , "Luciano Ramalho" , 2015 , "O'Reilly Media")

    );

    book9.isBorrowed = true;
    book9.borrowedBy = "Amir";

}
