
#include <iostream>
#include <limits>

#include "Book.h"
#include "User.h"

using namespace std;

int readInteger() {
    int value;

    while (!(cin >> value)) {
        if (cin.eof()) {
            return -1;
        }

        cout << "Invalid input! Enter a number: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return value;
}

int main() {
    BookList library;
    UserManager userManager;

    int choice;
    int id;
    int bookID;

    string title;
    string author;
    string name;

    // Load saved records when the program starts
    userManager.loadUsers();
    library.loadBooks();

    cout << "\n====================================";
    cout << "\n   LIBRARY MANAGEMENT SYSTEM";
    cout << "\n====================================";
    cout << "\nSaved records loaded successfully!\n";

    do {
        cout << "\n====================================";
        cout << "\n       LIBRARY MANAGEMENT SYSTEM";
        cout << "\n====================================";

        cout << "\n\n--- BOOK MANAGEMENT ---";
        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book by Title";
        cout << "\n4. Search Book by Author";
        cout << "\n5. Delete Book";
        cout << "\n6. Check Book Availability";

        cout << "\n\n--- TRANSACTION MANAGEMENT ---";
        cout << "\n7. Issue Book";
        cout << "\n8. Return Book";
        cout << "\n9. Reserve Book";

        cout << "\n\n--- USER MANAGEMENT ---";
        cout << "\n10. Add User";
        cout << "\n11. Display All Users";
        cout << "\n12. Search User";
        cout << "\n13. Update User";
        cout << "\n14. Delete User";

        cout << "\n\n15. Exit";
        cout << "\n\nEnter your choice: ";

        choice = readInteger();

        switch (choice) {
            case 1:
                cout << "\nEnter Book ID: ";
                id = readInteger();

                if (cin.eof()) break;

                cout << "Enter Book Title: ";
                getline(cin, title);

                cout << "Enter Author Name: ";
                getline(cin, author);

                library.addBook(id, title, author);
                break;

            case 2:
                library.displayBooks();
                break;

            case 3:
                cout << "\nEnter Book Title: ";
                getline(cin, title);

                library.searchByTitle(title);
                break;

            case 4:
                cout << "\nEnter Author Name: ";
                getline(cin, author);

                library.searchByAuthor(author);
                break;

            case 5:
                cout << "\nEnter Book ID to Delete: ";
                id = readInteger();

                library.deleteBook(id);
                break;

            case 6:
                cout << "\nEnter Book ID: ";
                id = readInteger();

                library.checkAvailability(id);
                break;

            case 7:
                cout << "\nEnter User ID: ";
                id = readInteger();

                if (cin.eof()) break;

                cout << "Enter Book ID: ";
                bookID = readInteger();

                library.issueBook(bookID, id, userManager);
                break;

            case 8:
                cout << "\nEnter User ID: ";
                id = readInteger();

                if (cin.eof()) break;

                cout << "Enter Book ID: ";
                bookID = readInteger();

                library.returnBook(bookID, id, userManager);
                break;

            case 9:
                cout << "\nEnter User ID: ";
                id = readInteger();

                if (cin.eof()) break;

                cout << "Enter Book ID: ";
                bookID = readInteger();

                library.reserveBook(bookID, id, userManager);
                break;

            case 10:
                cout << "\nEnter User ID: ";
                id = readInteger();

                if (cin.eof()) break;

                cout << "Enter User Name: ";
                getline(cin, name);

                userManager.addUser(id, name);
                break;

            case 11:
                userManager.displayUsers();
                break;

            case 12:
                cout << "\nEnter User ID: ";
                id = readInteger();

                userManager.searchUser(id);
                break;

            case 13:
                cout << "\nEnter User ID: ";
                id = readInteger();

                if (cin.eof()) break;

                cout << "Enter New Name: ";
                getline(cin, name);

                userManager.updateUser(id, name);
                break;

            case 14:
                cout << "\nEnter User ID: ";
                id = readInteger();

                userManager.deleteUser(id);
                break;

            case 15:
                cout << "\nExiting Library Management System...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

        // Save records after every menu operation
        userManager.saveUsers();
        library.saveBooks();

    } while (choice != 15 && !cin.eof());

    cout << "\nData saved successfully!";
    cout << "\nThank you for using Library Management System!\n";

    return 0;
}
