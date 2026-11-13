
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

#include "Book.h"
#include "User.h"

using namespace std;

BookList::BookList() {
    head = nullptr;
}

BookList::~BookList() {
    Book* current = head;

    while (current != nullptr) {
        Book* temp = current;
        current = current->next;
        delete temp;
    }
}

Book* BookList::findByID(int id) {
    Book* current = head;

    while (current != nullptr) {
        if (current->bookID == id) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

void BookList::addBook(int id, string title, string author) {
    if (id <= 0 || title.empty() || author.empty()) {
        cout << "\nInvalid book details!\n";
        return;
    }

    if (findByID(id) != nullptr) {
        cout << "\nBook ID already exists!\n";
        return;
    }

    Book* newBook = new Book(id, title, author);

    if (head == nullptr) {
        head = newBook;
    } else {
        Book* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newBook;
    }

    cout << "\nBook added successfully!\n";
}

void BookList::displayBooks() {
    if (head == nullptr) {
        cout << "\nNo books available in the system.\n";
        return;
    }

    Book* current = head;

    cout << "\n========== BOOK LIST ==========\n";

    while (current != nullptr) {
        cout << "\nBook ID: " << current->bookID;
        cout << "\nTitle: " << current->title;
        cout << "\nAuthor: " << current->author;

        cout << "\nAvailability: "
             << (current->available ? "Available" : "Issued");

        if (!current->available) {
            cout << "\nIssued To User ID: " << current->issuedTo;
        }

        cout << "\nReserved Users: ";

        if (current->reservationQueue.empty()) {
            cout << "No reservations";
        } else {
            queue<int> tempQueue = current->reservationQueue;

            while (!tempQueue.empty()) {
                cout << tempQueue.front() << " ";
                tempQueue.pop();
            }
        }

        cout << "\n------------------------------\n";

        current = current->next;
    }
}

void BookList::searchByTitle(string title) {
    Book* current = head;
    bool found = false;

    transform(title.begin(), title.end(), title.begin(),
              [](unsigned char c) {
                  return static_cast<char>(tolower(c));
              });

    while (current != nullptr) {
        string bookTitle = current->title;

        transform(bookTitle.begin(), bookTitle.end(), bookTitle.begin(),
                  [](unsigned char c) {
                      return static_cast<char>(tolower(c));
                  });

        if (bookTitle.find(title) != string::npos) {
            cout << "\nBook Found!";
            cout << "\nBook ID: " << current->bookID;
            cout << "\nTitle: " << current->title;
            cout << "\nAuthor: " << current->author << "\n";

            found = true;
        }

        current = current->next;
    }

    if (!found) {
        cout << "\nBook not found!\n";
    }
}

void BookList::searchByAuthor(string author) {
    Book* current = head;
    bool found = false;

    transform(author.begin(), author.end(), author.begin(),
              [](unsigned char c) {
                  return static_cast<char>(tolower(c));
              });

    while (current != nullptr) {
        string bookAuthor = current->author;

        transform(bookAuthor.begin(), bookAuthor.end(), bookAuthor.begin(),
                  [](unsigned char c) {
                      return static_cast<char>(tolower(c));
                  });

        if (bookAuthor.find(author) != string::npos) {
            cout << "\nBook Found!";
            cout << "\nBook ID: " << current->bookID;
            cout << "\nTitle: " << current->title;
            cout << "\nAuthor: " << current->author << "\n";

            found = true;
        }

        current = current->next;
    }

    if (!found) {
        cout << "\nBook not found!\n";
    }
}

void BookList::deleteBook(int id) {
    if (head == nullptr) {
        cout << "\nLibrary is empty!\n";
        return;
    }

    if (head->bookID == id) {
        if (!head->available) {
            cout << "\nCannot delete an issued book!\n";
            return;
        }

        if (!head->reservationQueue.empty()) {
            cout << "\nCannot delete a book with pending reservations!\n";
            return;
        }

        Book* temp = head;
        head = head->next;

        delete temp;

        cout << "\nBook deleted successfully!\n";
        return;
    }

    Book* current = head;

    while (current->next != nullptr &&
           current->next->bookID != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "\nBook not found!\n";
        return;
    }

    Book* temp = current->next;

    if (!temp->available) {
        cout << "\nCannot delete an issued book!\n";
        return;
    }

    if (!temp->reservationQueue.empty()) {
        cout << "\nCannot delete a book with pending reservations!\n";
        return;
    }

    current->next = temp->next;

    delete temp;

    cout << "\nBook deleted successfully!\n";
}

void BookList::checkAvailability(int id) {
    Book* book = findByID(id);

    if (book == nullptr) {
        cout << "\nBook not found!\n";
        return;
    }

    cout << "\nBook: " << book->title;

    if (book->available) {
        cout << "\nStatus: Available\n";
    } else {
        cout << "\nStatus: Currently Issued\n";
        cout << "Issued To User ID: " << book->issuedTo << "\n";
    }
}

bool BookList::issueBook(int bookID, int userID, UserManager& users) {
    Book* book = findByID(bookID);

    if (book == nullptr) {
        cout << "\nBook not found!\n";
        return false;
    }

    if (!book->available) {
        cout << "\nBook is already issued!\n";
        return false;
    }

    if (!book->reservationQueue.empty()) {
        cout << "\nThis book has pending reservations!\n";
        return false;
    }

    if (!users.incrementIssuedBooks(userID)) {
        return false;
    }

    book->available = false;
    book->issuedTo = userID;

    cout << "\nBook issued successfully!\n";

    return true;
}

bool BookList::returnBook(int bookID, int userID, UserManager& users) {
    Book* book = findByID(bookID);

    if (book == nullptr) {
        cout << "\nBook not found!\n";
        return false;
    }

    if (book->available) {
        cout << "\nThis book is not currently issued!\n";
        return false;
    }

    if (book->issuedTo != userID) {
        cout << "\nThis book was not issued to this user!\n";
        return false;
    }

    if (!users.decrementIssuedBooks(userID)) {
        return false;
    }

    book->available = true;
    book->issuedTo = 0;

    cout << "\nBook returned successfully!\n";

    while (!book->reservationQueue.empty()) {
        int nextUserID = book->reservationQueue.front();
        book->reservationQueue.pop();

        if (!users.userExists(nextUserID)) {
            continue;
        }

        if (users.incrementIssuedBooks(nextUserID)) {
            book->available = false;
            book->issuedTo = nextUserID;

            cout << "\nBook automatically assigned!\n";
            cout << "Next User ID: " << nextUserID << "\n";

            return true;
        }
    }

    cout << "\nNo reservations found.";
    cout << "\nBook is now available for issuing.\n";

    return true;
}

bool BookList::reserveBook(int bookID, int userID, UserManager& users) {
    Book* book = findByID(bookID);

    if (book == nullptr) {
        cout << "\nBook not found!\n";
        return false;
    }

    if (!users.userExists(userID)) {
        cout << "\nUser not found!\n";
        return false;
    }

    if (book->available) {
        cout << "\nBook is available. You can issue it directly!\n";
        return false;
    }

    if (book->issuedTo == userID) {
        cout << "\nYou already have this book!\n";
        return false;
    }

    queue<int> tempQueue = book->reservationQueue;

    while (!tempQueue.empty()) {
        if (tempQueue.front() == userID) {
            cout << "\nYou have already reserved this book!\n";
            return false;
        }

        tempQueue.pop();
    }

    book->reservationQueue.push(userID);

    cout << "\nBook reserved successfully!\n";
    cout << "Your position in queue: "
         << book->reservationQueue.size() << "\n";

    return true;
}

// Load books and reservation queues from file
void BookList::loadBooks() {
    ifstream file("data/books.txt");

    if (!file.is_open()) {
        return;
    }

    int id;
    int issuedTo;
    int reservationCount;
    bool available;
    string title;
    string author;

    while (file >> id >> available >> issuedTo
                >> quoted(title) >> quoted(author)
                >> reservationCount) {

        if (id <= 0 || reservationCount < 0 ||
            findByID(id) != nullptr) {
            break;
        }

        Book* newBook = new Book(id, title, author);

        newBook->available = available;
        newBook->issuedTo = issuedTo;

        for (int i = 0; i < reservationCount; i++) {
            int userID;

            if (!(file >> userID)) {
                break;
            }

            newBook->reservationQueue.push(userID);
        }

        if (head == nullptr) {
            head = newBook;
        } else {
            Book* current = head;

            while (current->next != nullptr) {
                current = current->next;
            }

            current->next = newBook;
        }
    }

    file.close();
}

// Save books and reservation queues to file
void BookList::saveBooks() const {
    ofstream file("data/books.txt");

    if (!file.is_open()) {
        cout << "\nError: Could not save book records!\n";
        return;
    }

    Book* current = head;

    while (current != nullptr) {
        file << current->bookID << " "
             << current->available << " "
             << current->issuedTo << " "
             << quoted(current->title) << " "
             << quoted(current->author) << " "
             << current->reservationQueue.size();

        queue<int> tempQueue = current->reservationQueue;

        while (!tempQueue.empty()) {
            file << " " << tempQueue.front();
            tempQueue.pop();
        }

        file << "\n";

        current = current->next;
    }

    file.close();
}
