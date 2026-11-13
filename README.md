# Library Management System

A menu-driven Library Management System developed in **C++** to demonstrate core Data Structures and Algorithms concepts, modular programming, and file handling.

## Project Overview

The application helps manage books, library users, book issue and return operations, and reservation requests. It uses different data structures for different types of records and stores data in local text files so records can be loaded again when the program restarts.

## Features

### Book Management
- Add and display books
- Search books by title or author
- Check book availability
- Delete eligible book records

### User Management
- Register and display users
- Search users by ID
- Update user names
- Delete eligible user records

### Circulation and Reservations
- Issue books to registered users
- Return books with borrower validation
- Reserve books that are currently issued
- Process reservations in First-In, First-Out (FIFO) order
- Automatically assign a returned book to the next eligible user in the queue

### File Handling
- Load book and user records when the application starts
- Save records after menu operations
- Store book and reservation information in `data/books.txt`
- Store user information in `data/users.txt`

## Screenshots

### Main Menu
![Library Management System main menu](screenshots/main_menu.png)

### Book List
![Display all books](screenshots/book_list.png)

### Issue Book
![Book issued successfully](screenshots/issue_book.png)

### Return Book
![Book returned successfully](screenshots/return_book.png)

### Reservation Validation
![System prevents reservation when the book is already issued](screenshots/reservation-already-issued.png)

The reservation validation example shows User ID `202` attempting to reserve Book ID `103`, which is already issued. The system responds with **"Book is already issued!"**.

> Add the screenshot images to the `screenshots/` folder using the filenames shown above so they appear in this section on GitHub.

## Data Structures Used

| Data Structure | Usage |
|---|---|
| Array | Stores user records (maximum capacity: 100 users) |
| Singly Linked List | Stores and manages book records |
| Queue | Maintains book reservation requests in FIFO order |
| File Streams | Persists book and user data between program runs |

## Project Structure

```text
Library_Management/
├── include/
│   ├── Book.h
│   └── User.h
├── src/
│   ├── main.cpp
│   ├── Book.cpp
│   └── User.cpp
├── data/
│   ├── books.txt
│   └── users.txt
├── screenshots/
├── docs/
├── Library_Management_System.docx
└── .gitignore
```

## Requirements

- Windows, Linux, or macOS
- GCC with C++17 support (or another compatible C++17 compiler)
- Visual Studio Code or any C++ editor (optional)

## Build and Run

Run these commands from the project root directory.

### Compile

```bash
g++ -std=c++17 -Wall -Wextra -I include src/main.cpp src/Book.cpp src/User.cpp -o LibraryManagement
```

On Windows, you can use an executable name with the `.exe` extension:

```powershell
g++ -std=c++17 -Wall -Wextra -I include src/main.cpp src/Book.cpp src/User.cpp -o LibraryManagement.exe
.\LibraryManagement.exe
```

On Linux or macOS, run:

```bash
./LibraryManagement
```

**Important:** Run the executable from the project root directory. The `data` directory must exist so the application can read and write `books.txt` and `users.txt`. The text files can be created by the application when it first saves data, but the directory itself should already exist.

## Testing

The project has been manually tested for core operations and common invalid cases, including duplicate IDs, invalid IDs, unavailable books, incorrect return users, deletion restrictions, reservation duplicates, FIFO reservation assignment, and loading saved records after restarting the application.

## Documentation

The repository includes a project report in `Library_Management_System.docx`. See the repository files for the report.

## Future Enhancements

- Replace text-file storage with SQLite or MySQL
- Add login and role-based access
- Add due dates, overdue tracking, and fine calculation
- Develop a graphical or web-based interface
- Add reports, backups, and stronger file validation

## Author

**Aditya Patel**

---

This project was developed as an academic MCA / Data Structures and Algorithms project.
