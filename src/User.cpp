
#include <iostream>
#include <fstream>
#include <iomanip>
#include "User.h"

using namespace std;

UserManager::UserManager() {
    userCount = 0;
}

int UserManager::findUserIndex(int id) const {
    for (int i = 0; i < userCount; i++) {
        if (users[i].userID == id) {
            return i;
        }
    }

    return -1;
}

bool UserManager::userExists(int id) const {
    return findUserIndex(id) != -1;
}

void UserManager::addUser(int id, string name) {
    if (id <= 0 || name.empty()) {
        cout << "\nInvalid user details!\n";
        return;
    }

    if (userCount >= MAX_USERS) {
        cout << "\nUser limit reached!\n";
        return;
    }

    if (findUserIndex(id) != -1) {
        cout << "\nUser ID already exists!\n";
        return;
    }

    users[userCount].userID = id;
    users[userCount].name = name;
    users[userCount].issuedBooks = 0;

    userCount++;

    cout << "\nUser added successfully!\n";
}

void UserManager::displayUsers() const {
    if (userCount == 0) {
        cout << "\nNo users registered!\n";
        return;
    }

    cout << "\n========== USER LIST ==========\n";

    for (int i = 0; i < userCount; i++) {
        cout << "\nUser ID: " << users[i].userID;
        cout << "\nName: " << users[i].name;
        cout << "\nIssued Books: " << users[i].issuedBooks;
        cout << "\n------------------------------\n";
    }
}

void UserManager::searchUser(int id) const {
    int index = findUserIndex(id);

    if (index == -1) {
        cout << "\nUser not found!\n";
        return;
    }

    cout << "\n========== USER FOUND ==========\n";
    cout << "\nUser ID: " << users[index].userID;
    cout << "\nName: " << users[index].name;
    cout << "\nIssued Books: " << users[index].issuedBooks << "\n";
}

void UserManager::updateUser(int id, string newName) {
    int index = findUserIndex(id);

    if (index == -1) {
        cout << "\nUser not found!\n";
        return;
    }

    if (newName.empty()) {
        cout << "\nName cannot be empty!\n";
        return;
    }

    users[index].name = newName;

    cout << "\nUser updated successfully!\n";
}

void UserManager::deleteUser(int id) {
    int index = findUserIndex(id);

    if (index == -1) {
        cout << "\nUser not found!\n";
        return;
    }

    if (users[index].issuedBooks > 0) {
        cout << "\nCannot delete user with issued books!\n";
        return;
    }

    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }

    userCount--;

    cout << "\nUser deleted successfully!\n";
}

bool UserManager::incrementIssuedBooks(int id) {
    int index = findUserIndex(id);

    if (index == -1) {
        cout << "\nUser not found!\n";
        return false;
    }

    users[index].issuedBooks++;
    return true;
}

bool UserManager::decrementIssuedBooks(int id) {
    int index = findUserIndex(id);

    if (index == -1) {
        cout << "\nUser not found!\n";
        return false;
    }

    if (users[index].issuedBooks <= 0) {
        cout << "\nNo issued books found!\n";
        return false;
    }

    users[index].issuedBooks--;
    return true;
}

// Load users from file
void UserManager::loadUsers() {
    ifstream file("data/users.txt");

    if (!file.is_open()) {
        return;
    }

    userCount = 0;

    int id;
    int issuedBooks;
    string name;

    while (userCount < MAX_USERS &&
           file >> id >> issuedBooks >> quoted(name)) {

        if (id <= 0 || issuedBooks < 0 || userExists(id)) {
            continue;
        }

        users[userCount].userID = id;
        users[userCount].name = name;
        users[userCount].issuedBooks = issuedBooks;

        userCount++;
    }

    file.close();
}

// Save users to file
void UserManager::saveUsers() const {
    ofstream file("data/users.txt");

    if (!file.is_open()) {
        cout << "\nError: Could not save user records!\n";
        return;
    }

    for (int i = 0; i < userCount; i++) {
        file << users[i].userID << " "
             << users[i].issuedBooks << " "
             << quoted(users[i].name) << "\n";
    }

    file.close();
}
