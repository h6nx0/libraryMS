# libraryMS
### A console-based Library Management System in C++

> "Built with blood, sweat, and an unreasonable amount of C++"

---

## Table of Contents
1. [Project Overview](#1-project-overview)
2. [Features](#2-features)
3. [System Requirements](#3-system-requirements)
4. [Project Structure](#4-project-structure)
5. [Setup & Installation](#5-setup--installation)
6. [How to Run](#6-how-to-run)
7. [Data File Formats](#7-data-file-formats)
8. [Usage Guide](#8-usage-guide)
9. [Known Limitations](#9-known-limitations)
10. [Author](#10-author)

---

## 1. Project Overview

Library Management System is a console-based C++ application that allows librarians to manage books, members, borrowing transactions, and fines. It features file-based persistence so all data is saved between sessions.

The system supports a full login mechanism for librarians, and tracks every borrow/return transaction with an optional fine system for overdue books.

---

## 2. Features

**Books Management**
- Add, edit, remove, and search books
- Track available vs. total copies per book
- Identify books by unique ISBN

**Members Management**
- Add, edit, and remove library members
- Auto-generated unique Member IDs (format: `ABC-XXXX`)
- Track borrowed books and outstanding fines per member
- View full borrowing history of any member

**Librarians Management**
- Add, edit, and remove librarian accounts (max 20)
- Each librarian has a unique ID (format: `LIB-XX`) and password
- Secure login with attempt limits (3 ID attempts, 3 password attempts per ID)

**Transactions**
- Borrow a book against a Member ID
- Return a book with automatic fine calculation (triggered if kept beyond 14 days)
- Dedicated fine mechanism to manually adjust fines
- All transactions logged and persisted to file

**Reports**
- View all transactions (borrow and return records)

**Session Summary**
- Displayed on exit, showing all additions, removals, borrows, and returns made during the session

---

## 3. System Requirements

| | |
|---|---|
| **OS** | Windows (required; uses `windows.h`, `system("cls")`, `Sleep()`) |
| **Compiler** | g++ / MinGW or MSVC |
| **C++ Standard** | C++11 or later |
| **Libraries** | iostream, cstdlib, limits, windows.h, fstream, sstream, ctime, string, vector |

---

## 4. Project Structure

```
libraryMS/
│
├── main.cpp
│
└── data/
    ├── books.txt
    ├── members.txt
    ├── librarians.txt
    └── transactions.txt
```

> **Note:** The `data/` folder and its `.txt` files must exist before running the program. If missing, the loader will report the file as not found and skip loading. The program will still run but with no pre-loaded data.

---

## 5. Setup & Installation

**Step 1** — Clone the repository:
```bash
git clone https://github.com/h6nx0/libraryMS.git
cd libraryMS
```

**Step 2** — Create the data directory and empty seed files:
```bash
mkdir data
echo. > data\books.txt
echo. > data\members.txt
echo. > data\librarians.txt
echo. > data\transactions.txt
```

**Step 3** — Seed at least one librarian into `data\librarians.txt` so you can log in. Format is pipe-separated with no spaces around pipes:
```
Name|ID|Password
```
Example:
```
Admin|LIB-10|admin123
```

**Step 4** — Compile:
```bash
g++ -o lms main.cpp
```

**Step 5** — Run:
```bash
lms.exe
```

---

## 6. How to Run

1. Launch the executable — data files load automatically from `data/`
2. Log in with a valid Librarian ID and password
   - 3 attempts allowed for ID, 3 for password
   - Exhausting all attempts exits the program
3. Navigate via numbered menus
   - Enter `9` to return to the Main Menu
   - Enter `0` to quit
4. On quit, a Session Summary is shown if any actions were performed
5. All changes are saved to file automatically after each relevant action

---

## 7. Data File Formats

All files are plain text, pipe-delimited (`|`).

**books.txt**
```
ISBN|Title|Author|Genre|AvailableCopies|TotalCopies
```
```
978-0132350884|Clean Code|Robert C. Martin|Programming|3|5
```

**members.txt**
```
ID|Name|RollNumber|Department|PhoneNumber|FineAmount|ISBN1,ISBN2,...
```
```
ABC-1234|Ali Hassan|CS-101|Computer Science|03001234567|0|
```

**librarians.txt**
```
Name|ID|Password
```
```
Admin|LIB-10|admin123
```

**transactions.txt**
```
MemberID|BookISBN|DaysBorrowed|Returned(0 or 1)
```
```
ABC-1234|978-0132350884|7|1
```

> For members with no borrowed books, leave the last field empty — a trailing pipe is fine.

---

## 8. Usage Guide

**Borrowing a Book**
1. Go to Transactions → Borrow a Book
2. Enter the Member's ID
3. Enter the ISBN of the book to borrow
4. Enter the number of days until return

The member must exist, the book must have available copies, and the member must not already have that book borrowed.

**Returning a Book**
1. Go to Transactions → Return a Book
2. Enter the Member's ID
3. Enter the ISBN of the book being returned
4. Enter how many days the book was actually kept

If kept beyond 14 days, you will be prompted to enter a fine amount, which is added to the member's balance.

**Fine Management**
1. Go to Transactions → Fine Mechanism
2. Enter the Member's ID
3. View current fine, then choose to add or subtract an amount

Only applicable if the member has an outstanding fine.

**Removing a Member** — Only possible if they have no borrowed books and no outstanding fines.

**Removing a Book** — Only possible if all copies are available (none currently borrowed).

**Removing a Librarian** — At least one librarian must remain in the system at all times.

---

## 9. Known Limitations

- **Windows-only** — due to `windows.h` (`system("cls")`, `Sleep()`). Not compatible with Linux/macOS without modification.
- **Plaintext passwords** — librarian passwords are stored without encryption.
- **Manual fine entry** — no date-based automatic fine calculation; days are entered manually by the librarian at return time.
- **Case-sensitive search** — book search requires an exact match on title or author name.
- **Small librarian ID space** — `LIB-10` to `LIB-99` gives only 90 possible IDs; collision is theoretically possible at scale.

---

## 10. Author

**Hasan B.**

[![GitHub](https://img.shields.io/badge/GitHub-h6nx0-181717?logo=github)](https://github.com/h6nx0)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-h6nx0-0A66C2?logo=linkedin)](https://www.linkedin.com/in/h6nx0)

---

*Version 1.0 — Started 7th May, 2026*
