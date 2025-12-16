#ifndef BOOK_H
#define BOOK_H

#include <vector>
#include <string>
using namespace std;


// Define a class to store book information

class Book {

public:

    int code;
    string category;
    string title;
    string author;
    int Year;
    string publisher;
    bool isBorrowed = false;
    string borrowedBy = "";

    Book() {

        isBorrowed = false;
        borrowedBy = "";

    }


    Book (int c, string cate, string t, string a, int y, string pub) {

        code = c;
        category = cate;
        title = t;
        author = a;
        Year = y;
        publisher = pub;
        isBorrowed = false;
        borrowedBy = "";
    }
};


void listBooks(const vector <Book>& books);

void listBooksByCategory(const vector <Book>& books);

void initializeBooks(vector <Book>& books);

#endif  