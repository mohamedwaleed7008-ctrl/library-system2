#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <string>
#include "BOOK.H"

using namespace std;

class library {

private:

	vector <Book> books;


public:

	library();

	
	void loadBooksFromFile (const string & filename);

	void saveBooksToFile (const string & filename);

	void saveBooksToCSV (const string & filename);

	void loadBooksFromCSV (const string & filename);

	void askSaveBeforeExit (const string & dataFile, const string & csvFile);


	void showAllBooks() {

		listBooks(books);  // Book function
	}

	void showBooksByCategory() {

		listBooksByCategory(books); // Book function
	}

	void addBook();

	void deleteBook();

	void searchBook();

	void borrowBook();

	void returnBook();

	void showStatistics();


};


#endif