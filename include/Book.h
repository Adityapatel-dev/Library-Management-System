
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <queue>

using namespace std;

class UserManager;

struct Book {
    int bookID;
    string title;
    string author;
    bool available;
    int issuedTo;
    queue<int> reservationQueue;
    Book* next;

    Book(int id, string t, string a) {
        bookID = id;
        title = t;
        author = a;
        available = true;
        issuedTo = 0;
        next = nullptr;
    }
};

class BookList {
private:
    Book* head;
    Book* findByID(int id);

public:
    BookList();
    ~BookList();

    void addBook(int id, string title, string author);
    void displayBooks();
    void searchByTitle(string title);
    void searchByAuthor(string author);
    void deleteBook(int id);
    void checkAvailability(int id);

    bool issueBook(int bookID, int userID, UserManager& users);
    bool returnBook(int bookID, int userID, UserManager& users);
    bool reserveBook(int bookID, int userID, UserManager& users);

    void loadBooks();
    void saveBooks() const;
};

#endif
