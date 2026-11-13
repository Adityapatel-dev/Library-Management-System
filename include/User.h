
#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

const int MAX_USERS = 100;

struct User {
    int userID;
    string name;
    int issuedBooks;
};

class UserManager {
private:
    User users[MAX_USERS];
    int userCount;
    int findUserIndex(int id) const;

public:
    UserManager();

    void addUser(int id, string name);
    void displayUsers() const;
    void searchUser(int id) const;
    void updateUser(int id, string newName);
    void deleteUser(int id);

    bool incrementIssuedBooks(int id);
    bool decrementIssuedBooks(int id);
    bool userExists(int id) const;

    void loadUsers();
    void saveUsers() const;
};

#endif
