#include <iostream>
#include <vector>
#include <string>
#include "MAIN.H"
#include "ADMINMENU.H"
#include "USERMENU.H"
#include "LIBRARY.H"
using namespace std;

// Library object

library lib;


//  Check Admin Username Function

bool admin(string username, vector <string> admins) {

    for (string result : admins) {

        if (username == result) {

            return true;
        }
    }

    return false;
}



//  Login Function 

void login() {


    // Admins Data

    vector <string> admins = { "admin_mohamed","admin_mohab", "admin_ahmed", "admin_malak", "admin_farah", "admin_noor" };

    const string adminPassword = "1234";



    // User Data

    const string userUsername = "user";
    const string userPassword = "0000";

    string username, password;
    int choice;



    // Main System

    while (true) {

        cout << "\n===== Library System =====\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "0. Exit\n";

        cout << "Choose: ";
        cin >> choice;



        if (choice == 0) {

            cout << "Goodbye!\n";
            return;
        }


        // Admin Login 

        if (choice == 1) {

            while (true) {

                cout << "\nEnter admin username: ";
                cin >> username;

                cout << "Enter admin password: ";
                cin >> password;


                if (admin(username, admins) && password == adminPassword) {

                    cout << "\n✅ Admin login successful!\n";

                    adminmenu();
                    return;
                }


                else {

                    cout << "\n? Wrong admin username or password. Try again.\n";

                }
            }
        }


        // User Login 

        else if (choice == 2) {

            while (true) {


                cout << "\nEnter user username: ";
                cin >> username;

                cout << "Enter user password: ";
                cin >> password;


                if (username == userUsername && password == userPassword) {

                    cout << "\n✅ User login successful!\n";

                    usermenu();
                    return;
                }

                else {

                    cout << "\n? Wrong user username or password.\n";

                }
            }
        }

        else {

            cout << "\nInvalid choice.\n";
        }
    }
}


int main() {

    login();


    return 0;
}

