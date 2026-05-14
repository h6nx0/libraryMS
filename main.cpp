//07th of the May, 2026 - Started

#include <iostream>
#include <cstdlib> //Used Rand() in Main
#include <limits> //Used in input function to ignore a whole discarded stream
#include <windows.h> //system() function and sleep
#include <fstream> 
#include <sstream> //Stringstream used in files loader
#include <ctime> //For time(0)
#include <string>
#include <vector>

using namespace std;

//Standalone Functions

//Input Mechanism
int inputMechanismInt() {
    int input;
    bool check = false;
    cout << "Enter a Number:- ";

    while (check == false) {

        if(!(cin >> input) || input < 0) { //Single Read - Fail State check due to non-numeric input
            cout << "\nInvalid Input! Enter a correct Number." << endl;
            cin.clear(); //Fail State Clear
            //To clear buffers in input stream of any length upto newline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nRe-Enter a correct Number:- ";
        }

        else {
            cin.ignore();
            check = true;
        }

    }

    return input;
}

//Classes Section

//Base Abstract Class
class Person {
    private:
    string name;
    string id;

    public:
    //Constructor
    Person(string n, string i) {
        name = n;
        id = i;
    }

    //Getters (in string, because variables are also string) to fetch private variables in Derived Classes
    string getName() {
        return name;
    }

    string getID() {
        return id;
    }

    //Setters to set private variables
    void setName(string n) {
        name = n;
    }

    //Virtual Function
    virtual void display() = 0;

};

//Logical Book Class
class Book {
    private:
    string title;
    string author;
    string isbn;
    string genre;
    int totalCopies;
    int availableCopies;

    public:
    //Constructor
    Book(string t, string a, string i, string g, int av, int to) {
        title = t;
        author = a;
        isbn = i;
        genre = g;
        availableCopies = av;
        totalCopies = to;
    }

    //Getters to fetch private variables
    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    string getISBN() {
        return isbn;
    }

    string getGenre() {
        return genre;
    }

    int getTotalCopies() {
        return totalCopies;
    }

    int getAvailableCopies() {
        return availableCopies;
    }

    //Setters to set private variables
    void setTitle(string t) {
        title = t;
    }

    void setAuthor(string a) {
        author = a;
    }

    void setGenre(string g) {
        genre = g;
    }

    void setTotalCopies(int t) {
        int borrowed = totalCopies - availableCopies;
        totalCopies = t;
        availableCopies = totalCopies - borrowed;
    }

    //Increment and Decrement Mechanisms to automatically sort amount of copies while manipulation goes on
    void incrementCopies() {
        availableCopies++;
    }

    void decrementCopies() {
        availableCopies--;
    }

    //Display Function
    void display() {
        cout << "\n=========================" << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Genre: " << genre << endl;
        cout << "Copies: " << getAvailableCopies() << "/" << getTotalCopies() << " available" << endl;
        cout << "=========================" << endl;
    }

};

//Librarian Class derived from Public Class
class Librarian : public Person {
    private:
    string password;

    public:
    //Constructor
    Librarian(string n, string i, string p) : Person (n, i) {
        password = p;
    }

    //Getters to fetch private variables
    string getPassword() {
        return password;
    }

    void setPassword(string p) {
        password = p;
    }

    //Display Functions
    void welcome() {
        cout << "\n================================================" << endl;
        cout << "\n==   Welcome to Library Management System! ==\n" << endl;
        cout << "================================================" << endl;
        cout << "                Name: " << getName() << endl;
        cout << "                ID: " << getID() << endl;
        cout << "================================================" << endl;
    }

    void display() {
        cout << "\n=========================" << endl;
        cout << "Name:- \"" << getName() << "\"" << endl;
        cout << "ID:- \"" << getID() << "\"" << endl;
        cout << "=========================" << endl;
    }

};

//Member Class derived from Person Class
class Member : public Person {
    private:
    vector<string> borrowedISBNs;
    string rollNumber;
    string department;
    string phoneNumber;
    int fineAmount;

    public:
    //Constructor
    Member(string n, string i, string r, string d, string p, int f) : Person(n, i) {
        rollNumber = r;
        department = d;
        phoneNumber = p;
        fineAmount = f;

    }

    //Getters to fetch private variables
    vector<string> getBorrowedISBNs() {
        return borrowedISBNs;
    }

    string getRollNumber() {
        return rollNumber;
    }

    string getDepartment() {
        return department;
    }

    string getPhoneNumber() {
        return phoneNumber;
    }

    int getFineAmount() {
        return fineAmount;
    }

    void addFineAmount(int fine) {
        fineAmount = fineAmount + fine;
    }

    void removeFineAmount(int fine) {
        fineAmount = fineAmount - fine;
    }

    //Setters to set private variables
    void setRollNumber(string r) {
        rollNumber = r;
    }

    void setDepartment(string d) {
        department = d;
    }

    void setPhoneNumber(string p) {
        phoneNumber = p;
    }

    //Increment/Decrement for borrowedISBNs
    void addBorrowedISBNs(string isbn) {
        borrowedISBNs.push_back(isbn);
    }

    void removeBorrowedISBNs(string isbn) {
        // Searches through borrowedISBNs vector by index, and upon finding a match,
        // erases it using an iterator (begin() + i) pointing to that position, then breaks
        for(size_t i = 0; i < borrowedISBNs.size(); i++){
            if(borrowedISBNs[i] == isbn) {
                borrowedISBNs.erase(borrowedISBNs.begin() + i);
                break;
            }
        }
    }

    //Search Borrowed ISBN
    int searchBorrowedISBNs(string isbn) {
        int found = 0;

        for(size_t i = 0; i < borrowedISBNs.size(); i++) {
            if(isbn == borrowedISBNs[i])
            {
                found = 1;
                break;
            }
        }
        return found;
    }

    //Display Function
    void display() override {
        cout << "\n=========================" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Member ID: " << getID() << endl;
        cout << "Institution Roll Number (if any): " << rollNumber << endl;
        cout << "Department in Institution (if any): " << department << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Books Borrowed: " << borrowedISBNs.size() << endl;

        if(borrowedISBNs.size() > 0) {
            cout << "Borrowed Books' Details: " << endl;
            //Borrowed Books Loop
            for(size_t i = 0; i < borrowedISBNs.size(); i++) {
                cout << i + 1 << ":- " << borrowedISBNs[i] << endl;
            }
        }

        cout << "Fine Amount Due: Rs. " << fineAmount << endl;
        cout << "=========================" << endl;
    }

};

//Terminal Menus Display Class
class Display {
    public:
    //Librarian Input Menu

    //Main Menu
    void mainMenu() {
        system("cls");
        cout << "\n================================================" << endl;
        cout << "==                 Main Menu                  ==" << endl;
        cout << "================================================" << endl;
        cout << "1. Books" << endl;
        cout << "2. Members" << endl;
        cout << "3. Librarians" << endl;
        cout << "4. Transactions" << endl;
        cout << "5. Reports" << endl;
        cout << "6. About" << endl;
        cout << "\nEnter 0 to Quit the Program" << endl;
        cout << "================================================" << endl;

    }

    //Books Menu
    void booksMenu() {
        system("cls");
        cout << "\n=========================" << endl;
        cout << "1. Display all Books" << endl;
        cout << "2. Search Books" << endl;
        cout << "3. Add a Book" << endl;
        cout << "4. Edit a Book's data" << endl;
        cout << "5. Remove a Book" << endl;
        cout << "\nEnter 9 for Main Menu" << endl;
        cout << "Enter 0 to Quit the Program" << endl;
        cout << "=========================" << endl;
    
    }

    //Members Menu
    void membersMenu() {
        system("cls");
        cout << "\n=========================" << endl;
        cout << "1. Display all Members" << endl;
        cout << "2. Add a Member" << endl;
        cout << "3. Edit a Member's data" << endl;
        cout << "4. Remove a Member" << endl;
        cout << "5. Member History" << endl;
        cout << "\nEnter 9 for Main Menu" << endl;
        cout << "Enter 0 to Quit the Program" << endl;
        cout << "=========================" << endl;

    }

    //Librarians Menu
    void librariansMenu() {
        system("cls");
        cout << "\n=========================" << endl;
        cout << "1. Display all librarians" << endl;
        cout << "2. Add a Librarian" << endl;
        cout << "3. Edit a Librarian's data" << endl;
        cout << "4. Remove a Librarian" << endl;
        cout << "\nEnter 9 for Main Menu" << endl;
        cout << "Enter 0 to Quit the Program" << endl;
        cout << "=========================" << endl;
    }

    //Transactions Menu
    void transactionsMenu() {
        system("cls");
        cout << "\n=========================" << endl;
        cout << "1. Borrow a Book" << endl;
        cout << "2. Return a Book" << endl;
        cout << "3. Fine Mechanism (Show, Add or Subtract)" << endl;
        cout << "\nEnter 9 for Main Menu" << endl;
        cout << "Enter 0 to Quit the Program" << endl;
        cout << "=========================" << endl;

    }

    //Reports Menu
    void reportsMenu() {
        system("cls");
        cout << "\n=========================" << endl;
        cout << "1. Display all Transactions" << endl;
        cout << "\nEnter 9 for Main Menu" << endl;
        cout << "Enter 0 to Quit the Program" << endl;
        cout << "=========================" << endl;

    }

    //About Menu
    void aboutMenu() {
        system("cls");
        cout << "================================================" << endl;
        cout << "             ABOUT THIS PROGRAM             " << endl;
        cout << "================================================" << endl;
        cout << "\nLibrary Management System v1.0" << endl;
        cout << "Built with blood, sweat, and an unreasonable\n" <<
            "amount of C++ by the one, the only..." << endl;
        cout << "\n  Sir Wobblesworth McFloppington the Third\n" << endl;
        cout << "  (He is not actually a Sir. Or is he?)\n" << endl;
        cout << "A humble console-based system that lets you\n" <<
            "borrow books, return them, track members,\n" <<
            "and feel like a librarian without the\n" <<
            "cardigan and reading glasses.\n" << endl;
        cout << "Features:" << endl;
        cout << " - Books that don't judge you" << endl;
        cout << " - Members who hopefully return things" << endl;
        cout << " - Fines for those who don't" << endl;
        cout << " - A session summary nobody asked for" << endl;
        cout << "\nEnter 9 for Main Menu" << endl;
        cout << "Enter 0 to Quit the Program" << endl;
        cout << "================================================" << endl;

    }

};

//Transaction Class - Underived
class Transaction {
    private:
    string memberID;
    string bookISBN;
    int daysBorrowed;
    bool returned;

    public:
    //Constructor
    Transaction(string m, string b, int d) {
        memberID = m;
        bookISBN = b;
        daysBorrowed = d;
        returned = false;
    }

    //Return Bool Mechanism
    void markReturned() {
        returned = true;
    }

    //Getters to fetch private variables
    string getMemberID() {
        return memberID;
    }

    string getBookISBN() {
        return bookISBN;
    }

    int getDaysBorrowed() {
        return daysBorrowed;
    }

    bool getReturned() {
        return returned;
    }

    void setReturned(bool r) {
        returned = r;
    }

    //Display Function
    void display() {
        cout << "\n=========================" << endl;
        cout << "Member ID: " << memberID << endl;
        cout << "Book ISBN: " << bookISBN << endl;
        cout << "Days Borrowed: " << daysBorrowed << endl;
        if(returned == true) {
            cout << "Return Status: " << "Returned" << endl;
        }
        else {
            cout << "Return Status: " << "Not Returned" << endl;
        }
        cout << "=========================" << endl;
    }

};

//Engine - Library Class
class Library {
    private:
    vector<Book> books;
    vector<Member> members;
    vector<Librarian> librarians;
    vector<Transaction> transactions;

    //Session Counters
    int sessionBooks;
    int sessionMembers;
    int sessionLibrarians;
    int sessionRBooks;
    int sessionRMembers;
    int sessionRLibrarians;
    int sessionBorrows;
    int sessionReturns;

    public:
    //Default Constructor for Session Counters
    Library() {
        sessionBooks = 0;
        sessionMembers = 0;
        sessionLibrarians = 0;
        sessionRBooks = 0;
        sessionRMembers = 0;
        sessionRLibrarians = 0;
        sessionBorrows = 0;
        sessionReturns = 0;
    }

    //Getters to fetch private variables
    vector<Book> getBooks() {
        return books;
    }

    vector<Member> getMember() {
        return members;
    }

    vector<Librarian> getLibrarian() {
        return librarians;
    }

    vector<Transaction> getTransactions() {
        return transactions;
    }
    
    //File Handling
    //Read-File

    //Books
    //File Format is:-
    //ISBN | Title | Author | Genre | Available Copies | Total Copies
    void loadBooks() {
        //Loading File
        ifstream file("data/books.txt");

        //If not found
        if(!file) {
            cout << "\n== The file isn't found, try again. ==" << endl;
            return;
        }

        //Reading File
        string line;
        while(getline(file, line)) {
            stringstream ss(line);
            string field;
            
            getline(ss, field, '|');
            string isbn = field;

            getline(ss, field, '|');
            string title = field;

            getline(ss, field, '|');
            string author = field;

            getline(ss, field, '|');
            string genre = field;

            getline(ss, field, '|');
            int availableCopies = stoi(field);

            getline(ss, field, '|');
            int totalCopies = stoi(field);

            Book b(title, author, isbn, genre, availableCopies, totalCopies);
            books.push_back(b);
        }

        //Closing File
        file.close();
        cout << "\n== " << books.size() << " books loaded ==" << endl;

    }

    //Members
    //File Format is:-
    //ID | Name | Roll Number | Department | Phone Number | Fine Amount | Borrowed Books - b1, b2, b3...
    void loadMembers() {
        //Loading File
        ifstream file("data/members.txt");

        //If not found
        if(!file) {
            cout << "\n== The file isn't found, try again. ==" << endl;
            return;
        }

        //Reading File
        string line;
        while(getline(file, line)) {
            stringstream ss(line);
            string field;

            getline(ss, field, '|');
            string id = field;

            getline(ss, field, '|');
            string name = field;

            getline(ss, field, '|');
            string rollNumber = field;

            getline(ss, field, '|');
            string department = field;

            getline(ss, field, '|');
            string phoneNumber = field;

            getline(ss, field, '|');
            int fineAmount = stoi(field);

            Member m(name, id, rollNumber, department, phoneNumber, fineAmount);
            
            getline(ss, field, '|');
            //New stream and loop because this section is separate in its own in the line
            stringstream tt(field);
            string temp;
            while(getline(tt, temp, ',')) {
                m.addBorrowedISBNs(temp);
            }
            
            members.push_back(m);
        }

        //Closing File
        file.close();
        cout << "\n== " << members.size() << " members loaded ==" << endl;

    }

    //Librarianss
    //File Format is:-
    //Name | ID | Password
    void loadLibrarians() {
        //Loading File
        ifstream file("data/librarians.txt");

        //If not found
        if(!file) {
            cout << "\n== The file isn't found, try again. ==" << endl;
            return;
        }

        //Reading File
        string line;
        while(getline(file, line)) {
            stringstream ss(line);
            string field;
            
            getline(ss, field, '|');
            string name = field;

            getline(ss, field, '|');
            string id = field;

            getline(ss, field, '|');
            string password = field;

            Librarian l(name, id, password);
            librarians.push_back(l);
        }

        //Closing File
        file.close();
        cout << "\n== Librarians loaded ==" << endl;

    }

    //Transactions
    //File Format is:-
    //Member ID | Book ISBN | Borrowed Days | Returned
    void loadTransactions() {
        //Loading File
        ifstream file("data/transactions.txt");

        //If not found
        if(!file) {
            cout << "\n== The file isn't found, try again. ==" << endl;
            return;
        }

        //Reading File
        string line;
        while(getline(file, line)) {
            stringstream ss(line);
            string field;

            getline(ss, field, '|');
            string memberID = field;

            getline(ss, field, '|');
            string bookISBN = field;

            getline(ss, field, '|');
            int daysBorrowed = stoi(field);

            getline(ss, field, '|');
            bool returned = stoi(field);

            Transaction t(memberID, bookISBN, daysBorrowed);
            t.setReturned(returned);
            transactions.push_back(t);
        }

        //Closing File
        file.close();
        cout << "\n== " << transactions.size() << " transactions loaded ==" << endl;

    }

    //Write-File

    //Books
    //ISBN | Title | Author | Genre | Available Copies | Total Copies
    void saveBooks() {
        ofstream file("data/books.txt");

        for(size_t i = 0; i < books.size(); i++) {
            file << books[i].getISBN() << '|' << books[i].getTitle() << '|' 
            << books[i].getAuthor() << '|' << books[i].getGenre() << '|' 
            << books[i].getAvailableCopies() << '|' << books[i].getTotalCopies() << endl;
        }

        file.close();

    }

    //Members
    //Id | Name | Roll Number | Department | Phone Number | Fine Amount | Borrowed Books - b1, b2, b3...
    void saveMembers() {
        ofstream file("data/members.txt");

        for(size_t i =  0; i < members.size(); i++) {
            file << members[i].getID() << '|' << members[i].getName() << '|' 
            << members[i].getRollNumber() << '|' << members[i].getDepartment() << '|' 
            << members[i].getPhoneNumber() << '|' << members[i].getFineAmount() << '|';

            for(size_t j = 0; j < members[i].getBorrowedISBNs().size(); j++) {
                if (j == 0)
                {
                    file << members[i].getBorrowedISBNs()[j];
                }
                else {
                    file << ',' << members[i].getBorrowedISBNs()[j];
                }
            }

            file << endl;
        }

        file.close();
    }

    //Librarians
    //Name | ID | Password
    void saveLibrarians() {
        ofstream file("data/librarians.txt");

        for(size_t i = 0; i < librarians.size(); i++) {
            file << librarians[i].getName() << '|' << librarians[i].getID() << '|' 
            << librarians[i].getPassword() << endl;
        }

        file.close();

    }

    //Transactions
    //Member ID | Book ISBN | Borrowed Days | Returned
    void saveTransactions() {
        ofstream file("data/transactions.txt");

        for(size_t i = 0; i < transactions.size(); i++) {
            file << transactions[i].getMemberID() << '|' <<
            transactions[i].getBookISBN() << '|' <<
            transactions[i].getDaysBorrowed() << '|' <<
            transactions[i].getReturned() << endl;
        }

        file.close();

    }

    //Login Menu
    bool loginMenu() {
        string name;
        string id;
        string password;
        int attempts_i = 3;
        int attempts_p = 3;
        bool quit = false;

        system("cls");

        for(size_t a = 0; a < 3; a++) {
            cout << "Enter your ID:- ";
            cin >> id;
            cin.ignore();

            for(size_t i = 0; i < librarians.size(); i++) {
                if(id == librarians[i].getID())
                {
                    for(size_t j = 0; j < 3; j++) {
                        cout << "\nEnter your Password:- ";
                        getline(cin, password);

                        if(id == librarians[i].getID() && password == librarians[i].getPassword())
                        {
                            system("cls");
                            librarians[i].welcome();
                            cout << "\nPress Enter to Continue." << endl;
                            cin.get();
                            return quit;
                        }
                    
                        cout << "Wrong Password! Retry please." << endl;
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        system("cls");
                        cin.clear();
                        attempts_p--;

                        if(attempts_p > 0)
                        {
                            cout << "== Attempts Left: " << attempts_p << " ==" << endl;
                        }
                    }

                    quit = true;
                    return quit;
                }
            
            }

            cout << "No librarian found against given ID! Try again with a valid ID." << endl;
            cout << "\nPress Enter to Continue." << endl;
            cin.get();
            system("cls");
            cin.clear();
            attempts_i--;

            if(attempts_i > 0)
            {
                cout << "== Attempts Left: " << attempts_i << " ==" << endl;
            }
        }

        quit = true;
        return quit;

    }

    //Display Functions

    //Display all Books Function
    void displayAllBooks() {
        for(size_t i = 0; i < books.size(); i++) {
            books[i].display();
        }
    }

    //Display all Members Function
    void displayAllMembers() {
        for(size_t i = 0; i < members.size(); i++) {
            members[i].display();
        }
    }

    //Display all Librarians Function
    void displayAllLibrarians() {
        for(size_t i = 0; i < librarians.size(); i++) {
            librarians[i].display();
        }
    }

    //Display all Transactions Function
    void displayAllTransactions() {
        for(size_t i = 0; i < transactions.size(); i++) {
            transactions[i].display();
        }
    }

    //Add Functions

    //Add Book
    void addBook() {
        //Variable Declaration for Book Object
        string isbn;
        string title;
        string author;
        string genre;
        int totalCopies;
        int availableCopies;

        //Placeholder for Negation Check
        int c;

        //Input Field
        cout << "Enter the ISBN of book (format: xxx-xxxxxxxxxx):- ";
        getline(cin, isbn);

        //Check for already added books
        for(size_t i = 0; i < books.size(); i++) {
            if(isbn == books[i].getISBN())
            {
                cout << "A book with same ISBN already exists! Try with a different ISBN." << endl;
                return;
            }
        }

        cout << "Enter the title of book:- ";
        getline(cin, title);

        cout << "Enter the book author's name:- ";
        getline(cin, author);

        cout << "Enter the genre of the book:- ";
        getline(cin, genre);

        cout << "Enter the amount of total copies available:- ";
        cin >> c;
        cin.ignore();

        while(c < 0)
        {
            cout << "Sorry, learn basic mathematics first and then come here!\n" <<
            "Total number of books cannot be negative." << endl;
            cout << "Re-enter correct amount:- ";
            cin >> c;
            cin.ignore();
        }

        totalCopies = c;
        availableCopies = totalCopies;

        Book b(title, author, isbn, genre, availableCopies, totalCopies);
        books.push_back(b);
        cout << "\nBook \"" << title << "\" added successfully!" << endl;
        sessionBooks++;

    }

    //Add Member
    void addMember() {
        string name;
        string rollNumber;
        string department;
        string phoneNumber;
        string id;
        int fine;
        bool idExists = true;

        cout << "Enter Name of the new Member:- ";
        getline(cin, name);

        cout << "Enter Roll Number of the new Member if they have any:- ";
        getline(cin, rollNumber);

        cout << "Enter Department of the new Member:- ";
        getline(cin, department);

        cout << "Enter the Phone Number of the new Member:- ";
        getline(cin, phoneNumber);

        //Check for already added members
        for(size_t i = 0; i < members.size(); i++) {
            if(phoneNumber == members[i].getPhoneNumber())
            {
                cout << "A Member with same Phone Number already exists!\n" <<
                "Try with a different Phone Number." << endl;
                return;
            }
        }

        fine = 0;

        //ID Assignment Mechanism
        //Format:- ABC-XXXX
        string code = "";

        while (idExists == true) {
            code = "";
            idExists = false;
            for(size_t i = 0; i < 3; i++) {
                code = code + char('A' + rand() % 26);
            }

            code = code + '-';

            // + 1000 is because it can't guarantee 4 digits the other way
            int p_h = rand() % 9000 + 1000;
            code = code + to_string(p_h);

            //Check for already added members
            for(size_t i = 0; i < members.size(); i++) {
                if(code == members[i].getID())
                {
                    idExists = true;
                }
            }

        }

        id = code;

        cout << "Member ID Assigned to \"" << name << "\" is:- " << id << endl;

        Member m(name, id, rollNumber, department, phoneNumber, fine);
        members.push_back(m);
        cout << "\nMember \"" << name << "\" added successfully!" << endl;
        sessionMembers++;

    }

    //Add Librarian
    void addLibrarian() {
        string name;
        string id;
        string password;
        bool idExists = true;

        if(librarians.size() < 20)
        {
            cout << "Enter the name of new librarian:- ";
            getline(cin, name);

            cout << "\nEnter password for \"" << name << "\"'s login:- ";
            getline(cin, password);

            //ID Assignment Mechanism
            //Format:- LIB-XX
            string code = "";

            while (idExists == true) {
                code = "LIB";
                idExists = false;
                code = code + '-';

                // + 10 is because it can't guarantee 2 digits the other way
                int p_h = rand() % 90 + 10;
                code = code + to_string(p_h);

                //Check for already added librarians
                for(size_t i = 0; i < librarians.size(); i++) {
                    if(code == librarians[i].getID())
                    {
                        idExists = true;
                    }
                }

            }

            id = code;

            cout << "Librarian ID Assigned to \"" << name << "\" is:- " << id << endl;

            Librarian l(name, id, password);
            librarians.push_back(l);
            cout << "Librarian \"" << name << "\" added successfully!" << endl;
            sessionLibrarians++;
        }

        else {
            cout << "Librarian limit exceeded, remove any librarian first and try again!" << endl;
        }
    }


    //Remove Functions

    //Remove Book
    void removeBook() {
        string isbn;

        cout << "Enter the ISBN of book (format: xxx-xxxxxxxxxx):- ";
        getline(cin, isbn);

        //Check for books' record
        for(size_t i = 0; i < books.size(); i++) {
            if(isbn == books[i].getISBN())
            {
                cout << "Book \"" << books[i].getTitle() << "\" found against given ISBN." << endl;

                if(books[i].getAvailableCopies() == books[i].getTotalCopies())
                {
                    cout << "Removing the book..." << endl;

                    books.erase(books.begin() + i);
                    cout << "Book Successfully Removed!" << endl;
                    sessionRBooks++;
                    return;
                }
                
                else {
                    cout << "Clear borrowing record of the book in order to delete it!" << endl;
                    return;
                }
            }

        }

        cout << "No book found against given ISBN! Try again with a valid ISBN." << endl;

    }

    //Remove Member
    void removeMember() {
        string id;

        cout << "Enter the ID of member (format: xxx-xxxx):- ";
        getline(cin, id);

        //Check for members' record
        for(size_t i = 0; i < members.size(); i++) {
            if(id == members[i].getID())
            {
                cout << "Member \"" << members[i].getName() << "\" found against given ID." << endl;

                if(members[i].getBorrowedISBNs().size() == 0 && members[i].getFineAmount() == 0)
                {
                    cout << "Deleting member's data..." << endl;

                    members.erase(members.begin() + i);
                    cout << "Member Successfully Removed" << endl;
                    sessionRMembers++;
                    return;
                }

                else {
                    cout << "Please clear records against the member in order to delete their data!" << endl;
                    return;
                }
            }

        }

        cout << "No member found against given ID! Try again with a valid ID." << endl;

    }

    //Remove Librarian
    void removeLibrarian() {
        string id;

        cout << "Enter the ID of librarian (format: xxx-xx):- ";
        getline(cin, id);

        if(librarians.size() > 1)
        {
            //Check for librarians' record
            for(size_t i = 0; i < librarians.size(); i++) {
                if(id == librarians[i].getID())
                {
                    cout << "Librarian \"" << librarians[i].getName() << "\" found against given ID." << endl;
                    cout << "Deleting librarian's data..." << endl;

                    librarians.erase(librarians.begin() + i);
                    cout << "Librarian Removed Successfully!" << endl;
                    sessionRLibrarians++;
                    return;
                }

            }

            cout << "No librarian found against given ID! Try again with a valid ID." << endl;
        }

        else {
            cout << "There should atleast be one librarian in order to keep the system running!\n" <<
            "Add another librarian first." << endl;
        }

    }

    //Edit Functions

    //Edit Book
    //ISBN | Title | Author | Genre | Available Copies | Total Copies
    void editBook() {
        string isbn;
        string title;
        string author;
        string genre;
        int totalCopies;
        int choice;

        cout << "Enter the ISBN of book (format: xxx-xxxxxxxxxx):- ";
        getline(cin, isbn);

        //Check for books' record
        for(size_t i = 0; i < books.size(); i++) {
            if(isbn == books[i].getISBN())
            {
                cout << "Book \"" << books[i].getTitle() << "\" found against given ISBN." << endl;

                cout << "Edit options:- " << endl;
                cout << "1. Title" << endl;
                cout << "2. Author" << endl;
                cout << "3. Genre" << endl;
                cout << "4. Total Copies" << endl;
                cout << "5. Go back to Main Menu" << endl;

                choice = inputMechanismInt();

                switch (choice)
                {
                    case 1:
                        cout << "Enter new Title:- ";
                        getline(cin, title);

                        books[i].setTitle(title);
                        cout << "Title edited Successfully!" << endl;
                        break;
                    case 2:
                        cout << "Enter new Author:- ";
                        getline(cin, author);

                        books[i].setAuthor(author);
                        cout << "Author edited Successfully!" << endl;
                        break;
                    case 3:
                        cout << "Enter new Genre:- ";
                        getline(cin, genre);

                        books[i].setGenre(genre);
                        cout << "Genre edited Successfully!" << endl;
                        break;
                    case 4:
                        cout << "Enter new amount of Total Copies:- " << endl;
                        totalCopies = inputMechanismInt();

                        books[i].setTotalCopies(totalCopies);
                        cout << "Total Copies edited Successfully!" << endl;
                        break;
                    case 5:
                        return;
                    default:
                        cout << "\nInvalid Option! Press Enter.";
                        cin.get();
                }

                return;
            }
            
        }

        cout << "No book found against given ISBN! Try again with a valid ISBN." << endl;

    }

    //Edit Member
    //Id | Name | Roll Number | Department | Phone Number | Fine Amount | Borrowed Books - b1, b2, b3...
    void editMember() {
        string id;
        string name;
        string rollNumber;
        string department;
        string phoneNumber;
        int choice;

        cout << "Enter the ID of member (format: xxx-xxxx):- ";
        getline(cin, id);

        //Check for books' record
        for(size_t i = 0; i < members.size(); i++) {
            if(id == members[i].getID())
            {
                cout << "Member \"" << members[i].getName() << "\" found against given ID." << endl;

                cout << "Edit options:- " << endl;
                cout << "1. Name" << endl;
                cout << "2. Roll Number" << endl;
                cout << "3. Department" << endl;
                cout << "4. Phone Number" << endl;
                cout << "5. Go back to Main Menu" << endl;

                choice = inputMechanismInt();

                switch (choice)
                {
                    case 1:
                        cout << "Enter new Name:- ";
                        getline(cin, name);

                        members[i].setName(name);
                        cout << "Name edited Successfully!" << endl;
                        break;
                    case 2:
                        cout << "Enter new Roll Number:- ";
                        getline(cin, rollNumber);

                        members[i].setRollNumber(rollNumber);
                        cout << "Roll Number edited Successfully!" << endl;
                        break;
                    case 3:
                        cout << "Enter new Department:- ";
                        getline(cin, department);

                        members[i].setDepartment(department);
                        cout << "Department edited Successfully!" << endl;
                        break;
                    case 4:
                        cout << "Enter new Phone Number:- ";
                        getline(cin, phoneNumber);

                        members[i].setPhoneNumber(phoneNumber);
                        cout << "Phone Number edited Successfully!" << endl;
                        break;
                    case 5:
                        return;
                    default:
                        cout << "\nInvalid Option! Press Enter.";
                        cin.get();
                }

                return;
            }
            
        }

        cout << "No member found against given ID! Try again with a valid ID." << endl;

    }
    
    //Edit Librarian
    //Name | ID | Password
    void editLibrarian() {
        string id;
        string name;
        string password;
        int choice;

        cout << "Enter the ID of librarian (format: xxx-xx):- ";
        getline(cin, id);

        //Check for books' record
        for(size_t i = 0; i < librarians.size(); i++) {
            if(id == librarians[i].getID())
            {
                cout << "Librarian \"" << librarians[i].getName() << "\" found against given ID." << endl;

                cout << "Edit options:- " << endl;
                cout << "1. Name" << endl;
                cout << "2. Password" << endl;
                cout << "3. Go back to Main Menu" << endl;

                choice = inputMechanismInt();

                switch (choice)
                {
                    case 1:
                        cout << "Enter new Name:- ";
                        getline(cin, name);

                        librarians[i].setName(name);
                        cout << "Name edited Successfully!" << endl;
                        break;
                    case 2:
                        cout << "Enter new Password:- ";
                        getline(cin, password);

                        librarians[i].setPassword(password);
                        cout << "Password edited Successfully!" << endl;
                        break;
                    case 3:
                        return;
                    default:
                        cout << "\nInvalid Option! Press Enter.";
                        cin.get();
                }

                return;
            }
            
        }

        cout << "No librarian found against given ID! Try again with a valid ID." << endl;

    }

    //Search Books
    void searchBooks() {
        string search;
        bool found = false;

        cout << "Enter the books's title or author's name:- ";
        getline(cin, search);

        for(size_t i = 0; i < books.size(); i++) {
            if(search == books[i].getAuthor() || search == books[i].getTitle())
            {
                books[i].display();
                found = true;
            }
        }
        
        if(found == false)
        {
            cout << "Relative book(s) not found. Try with a different Title or Author." << endl;
        }
    }

    //Engine Functions

    //Borrow Book
    void borrowBook() {
        string b_id;
        string b_isbn;
        int b_days;
        int search;
        bool memberSearch = false;
        bool found = false;

        //Input
        cout << "Enter Membership-ID (format: ABC-xxxx) to make a Borrow request:- ";
        getline(cin, b_id);

        cout << "\nSearching Membership-ID..." << endl;

        //Member Fetch
        for(size_t i = 0; i < members.size(); i++) {
            if(b_id == members[i].getID())
            {
                cout << "Member \"" << members[i].getName() << "\" found for Relative ID." << endl;
                search = i;
                memberSearch = true;
                break;
            }
        }

        if (memberSearch == false)
        {
            cout << "Member not found!\n" <<
            "Make sure that the format is correct or whether the Member is added." << endl;
            return;
        }

        //Book Input
        cout << "Enter the ISBN for the required book (format: xxx-xxxxxxxxxx):- ";
        getline(cin, b_isbn);

        cout << "\nSearching the ISBN..." << endl;

        //ISBN Search
        for(size_t i = 0; i < books.size(); i++) {
            if(b_isbn == books[i].getISBN() && members[search].searchBorrowedISBNs(b_isbn) == 0 && books[i].getAvailableCopies() > 0)
            {
                cout << "Enter Number of Days till return:- ";
                b_days = inputMechanismInt();
                members[search].addBorrowedISBNs(b_isbn);
                books[i].decrementCopies();
                found = true;
                Transaction t(b_id, b_isbn, b_days);
                transactions.push_back(t);
                cout << "Book \"" << books[i].getTitle() << "\" Successfully Borrowed by \"" << members[search].getName() << "\"" << endl;
                cout << "\nPress Enter to Continue." << endl;
                cin.get();
                sessionBorrows++;
                return;
            }

            else if(b_isbn == books[i].getISBN() && books[i].getAvailableCopies() == 0)
            {
                cout << "No copies available for this book!" << endl;
                cout << "\nPress Enter to Continue." << endl;
                cin.get();
                return;
            }

            else if(b_isbn == books[i].getISBN() && members[search].searchBorrowedISBNs(b_isbn) == 1)
            {
                cout << "Book \"" << books[i].getTitle() << "\" has already been borrowed!" << endl;
                cout << "\nPress Enter to Continue." << endl;
                cin.get();
                found = true;
                return;
            }
        }

        if(found == false)
        {
            cout << "No book for given ISBN found!" << endl;
            cout << "\nPress Enter to Continue." << endl;
            cin.get();
            return;
        }

    }

    //Return Book
    void returnBook() {
        string b_id;
        string b_isbn;
        int fine;
        int search;
        int days;
        bool memberSearch = false;
        bool found = false;

        //Input
        cout << "Enter Membership-ID (format: ABC-xxxx) to make a Return request:- ";
        getline(cin, b_id);

        cout << "\nSearching Membership-ID..." << endl;

        //Member Fetch
        for(size_t i = 0; i < members.size(); i++) {
            if(b_id == members[i].getID())
            {
                cout << "Member \"" << members[i].getName() << "\" found for Relative ID." << endl;
                search = i;
                memberSearch = true;
                break;
            }
        }

        if (memberSearch == false)
        {
            cout << "Member not found!\n" <<
            "Make sure that the format is correct or whether the Member is added." << endl;
            return;
        }

        //Book Input
        cout << "Enter the ISBN for the book intended for Return (format: xxx-xxxxxxxxxx):- ";
        getline(cin, b_isbn);

        cout << "\nSearching the ISBN..." << endl;

        //ISBN Search
        for(size_t i = 0; i < books.size(); i++) {
            if(b_isbn == books[i].getISBN() && members[search].searchBorrowedISBNs(b_isbn) == 1)
            {
                //Fine Calculation
                cout << "How many days was the book kept?" << endl;
                days = inputMechanismInt();
                if(days > 14)
                {
                    cout << "\nCurrent Fine:- " << members[search].getFineAmount() << endl;
                    cout << "Days threshold surpassed, what should be the Fine?" << endl;
                    fine = inputMechanismInt();
                    // while(fine < 0) {
                    //     cout << "\nFine cannot be negative, Re-enter:- ";
                    //     cin >> fine;
                    //     cin.ignore();
                    // }
                    members[search].addFineAmount(fine);
                    members[search].removeBorrowedISBNs(b_isbn);
                    books[i].incrementCopies();
                    found = true;
                    Transaction t(b_id, b_isbn, days);
                    t.markReturned();
                    transactions.push_back(t);
                    cout << "\nBook \"" << books[i].getTitle() << "\" Successfully Returned by \"" << members[search].getName() << "\"" << endl;
                    cout << "Fine:- " << members[search].getFineAmount() << endl;
                    cout << "\nPress Enter to Continue." << endl;
                    cin.get();
                    sessionReturns++;
                    return;
                }
                else {
                    members[search].removeBorrowedISBNs(b_isbn);
                    books[i].incrementCopies();
                    found = true;
                    Transaction t(b_id, b_isbn, days);
                    t.markReturned();
                    transactions.push_back(t);
                    cout << "\nBook \"" << books[i].getTitle() << "\" Returned!" << endl;
                    cout << "No fine issued!" << endl;
                    cout << "\nPress Enter to Continue." << endl;
                    cin.get();
                    sessionReturns++;
                    return;
                }
                
            }

            else if(b_isbn == books[i].getISBN() && members[search].searchBorrowedISBNs(b_isbn) == 0)
            {
                cout << "Book \"" << books[i].getTitle() << "\" has already been returned or was not borrowed!" << endl;
                cout << "\nPress Enter to Continue." << endl;
                cin.get();
                found = true;
                return;
            }
        }

        if(found == false)
        {
            cout << "No book for given ISBN found!" << endl;
            cout << "\nPress Enter to Continue." << endl;
            cin.get();
            return;
        }

    }

    //Member History
    void displayMemberHistory() {
        string b_id;
        bool memberSearch = false;
        bool found = false;

        //Input
        cout << "Enter Membership-ID to proceed:- ";
        getline(cin, b_id);

        cout << "\nSearching Membership-ID..." << endl;

        //Member Fetch
        for(size_t i = 0; i < members.size(); i++) {
            if(b_id == members[i].getID())
            {
                cout << "Member \"" << members[i].getName() << "\" found for Relative ID." << endl;
                memberSearch = true;
                break;
            }
        }

        if (memberSearch == false)
        {
            cout << "Member not found!\n" <<
            "Make sure that the format is correct or whether the Member is added." << endl;
            return;
        }

        for(size_t i = 0; i < transactions.size(); i++) {
            if(b_id == transactions[i].getMemberID())
            {
                transactions[i].display();
                found = true;
            }

        }

        if(found == false)
        {
            cout << "== Respected Member does not possess any Borrowing Record! ==" << endl;
        }

    }

    //Fine Mechanism
    void fineMechanism() {
        string b_id;
        int fine;
        int search;
        int select;
        bool memberSearch = false;

        //Input
        cout << "Enter Membership-ID (format: XXX-XXXX) to make a Fine transaction request:- ";
        getline(cin, b_id);

        cout << "\nSearching Membership-ID..." << endl;

        //Member Fetch
        for(size_t i = 0; i < members.size(); i++) {
            if(b_id == members[i].getID())
            {
                cout << "Member \"" << members[i].getName() << "\" found for Relative ID." << endl;
                search = i;
                memberSearch = true;
                break;
            }
        }

        if(memberSearch == true && members[search].getFineAmount() > 0)
        {
            cout << "The Fine for Member \"" << members[search].getName() << "\" is:- Rs. " << members[search].getFineAmount() << endl;
            cout << "1. Add to Fine" << endl;
            cout << "2. Subtract from Fine" << endl;
            select = inputMechanismInt();
            cout << endl;
            
            if(select == 1)
            {
                cout << "Enter the Amount to add in Fine:- Rs. ";

                if(!(cin >> fine)) { //Single Read - Fail State check due to non-numeric input
                    cout << "\nInvalid Input! Try again later." << endl;
                    cin.clear(); //Fail State Clear
                    cin.ignore(1000);
                    return;
                }

                else {
                    cin.ignore();
                    if(fine > 0)
                    {
                        members[search].addFineAmount(fine);
                        saveMembers();
                        cout << "\nCalculation Performed Successfully!" << endl;
                        cout << "The updated Fine for Member \"" << members[search].getName() << "\" is:- Rs. " << members[search].getFineAmount() << endl;
                    }

                    else {
                        cout << "\nInvalid Amount! Re-try later." << endl;
                    }
                }
            }

            else if(select == 2)
            {
                cout << "Enter the Amount to subtract from Fine:- Rs. ";

                if(!(cin >> fine)) { //Single Read - Fail State check due to non-numeric input
                    cout << "\nInvalid Input! Try again later." << endl;
                    cin.clear(); //Fail State Clear
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return;
                }

                else {
                    cin.ignore();
                    if(fine > 0)
                    {
                        members[search].removeFineAmount(fine);
                        saveMembers();
                        cout << "\nCalculation Performed Successfully!" << endl;
                        cout << "The updated Fine for Member \"" << members[search].getName() << "\" is:- Rs. " << members[search].getFineAmount() << endl;
                    }

                    else {
                        cout << "\nInvalid Amount! Re-try later." << endl;
                    }
                }
            }
                
        }

        else if (memberSearch == false)
        {
            cout << "Member not found!\n" <<
            "Make sure that the format is correct or whether the Member is added." << endl;
            return;
        }

        else {
            cout << "The Member \"" << members[search].getName() << "\" has no outstanding fine." << endl;
        }

    }

    //Conclusive Function

    //Session Summary
    void sessionSummary() {
        if(sessionBooks > 0 || sessionMembers > 0 ||  sessionLibrarians > 0 || sessionRBooks > 0 || sessionRMembers > 0 || sessionRLibrarians > 0 || sessionBorrows > 0 || sessionReturns > 0)
        {
            cout << "\n=========================" << endl;
            cout << "==== Session Summary ====" << endl;
            cout << "=========================" << endl;
            if(sessionBooks > 0)
            {
                cout << "Books Added:- " << sessionBooks << endl;
            }
            if(sessionMembers > 0)
            {
                cout << "Members Added:- " << sessionMembers << endl;
            }
            if(sessionLibrarians > 0)
            {
                cout << "Librarians Added:- " << sessionLibrarians << endl;
            }
            if(sessionRBooks > 0)
            {
                cout << "Books Removed:- " << sessionRBooks << endl;
            }
            if(sessionRMembers > 0)
            {
                cout << "Members Removed:- " << sessionRMembers << endl;
            }
            if(sessionRLibrarians > 0)
            {
                cout << "Librarians Removed:- " << sessionRLibrarians << endl;
            }
            if(sessionBorrows > 0)
            {
                cout << "Books Borrowed:- " << sessionBorrows << endl;
            }
            if(sessionReturns > 0)
            {
                cout << "Books Returned:- " << sessionReturns << endl;
            }
            cout << "=========================" << endl;
        }
        
    }

};

//Main Function
int main()
{
    //Variable Selector
    int select;
    bool quit = false;

    srand(time(0));

    //Object Declaration 
    Display d;
    Library l;

    //Terminal Junk Cleaner
    system("cls");

    //Load Files
    l.loadBooks();
    l.loadMembers();
    l.loadLibrarians();
    l.loadTransactions();

    Sleep(2000);
    //Librarian Menu
    quit = l.loginMenu();

    //Main Loop
    while(!quit) {
        //Main Menu
        d.mainMenu();
        select = inputMechanismInt();

        switch (select)
        {
            case 1:
                d.booksMenu();
                select = inputMechanismInt();

                switch (select)
                {
                    case 1:
                        l.displayAllBooks();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        break;
                     case 2:
                        l.searchBooks();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        break;
                    case 3:
                        l.addBook();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        l.saveBooks();
                        break;
                    case 4:
                        l.editBook();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        l.saveBooks();
                        break;
                    case 5:
                        l.removeBook();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        l.saveBooks();
                        break;
                    case 9:
                        break;
                    case 0:
                        quit = true;
                        break;
                    default:
                        cout << "\nInvalid Option! Press Enter.";
                        cin.get();
                }

                break;
            case 2:
                d.membersMenu();
                select = inputMechanismInt();

                switch (select)
                {
                    case 1:
                        l.displayAllMembers();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        break;
                    case 2:
                        l.addMember();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        l.saveMembers();
                        break;
                    case 3:
                        l.editMember();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        l.saveMembers();
                        break;
                    case 4:
                        l.removeMember();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        l.saveMembers();
                        break;
                    case 5:
                        l.displayMemberHistory();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        break;
                    case 9:
                        break;
                    case 0:
                        quit = true;
                        break;
                    default:
                        cout << "\nInvalid Option! Press Enter.";
                        cin.get();
                }

                break;
            case 3:
                d.librariansMenu();
                select = inputMechanismInt();

                switch (select)
                {
                    case 1:
                        l.displayAllLibrarians();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        break;
                    case 2:
                        l.addLibrarian();
                        l.saveLibrarians();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        break;
                    case 3:
                        l.editLibrarian();
                        l.saveLibrarians();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        break;
                    case 4:
                        l.removeLibrarian();
                        l.saveLibrarians();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        break;
                    case 9:
                        break;
                    case 0:
                        quit = true;
                        break;
                    default:
                        cout << "\nInvalid Option! Press Enter.";
                        cin.get();
                }

                break;
            case 4:
                d.transactionsMenu();
                select = inputMechanismInt();

                switch (select)
                {
                    case 1:
                        l.borrowBook();
                        // cin.get();
                        l.saveBooks();
                        l.saveMembers();
                        l.saveTransactions();
                        break;
                    case 2:
                        l.returnBook();
                        // cin.get();
                        l.saveBooks();
                        l.saveMembers();
                        l.saveTransactions();
                        break;
                    case 3:
                        l.fineMechanism();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        l.saveMembers();
                        break;
                    case 9:
                        break;
                    case 0:
                        quit = true;
                        break;
                    default:
                        cout << "\nInvalid Option! Press Enter.";
                        cin.get();
                }

                break;
            case 5:
                d.reportsMenu();
                select = inputMechanismInt();

                switch (select)
                {
                    case 1:
                        l.displayAllTransactions();
                        cout << "\nPress Enter to Continue." << endl;
                        cin.get();
                        break;
                    case 9:
                        break;
                    case 0:
                        quit = true;
                        break;
                    default:
                        cout << "\nInvalid Option! Press Enter.";
                        cin.get();
                }

                break;
            case 6:
                d.aboutMenu();
                select = inputMechanismInt();

                switch (select)
                {
                    case 9:
                        break;
                    case 0:
                        quit = true;
                        break;
                    default:
                        cout << "\nInvalid Option! Press Enter.";
                        cin.get();
                }

                break;
            case 0:
                quit = true;
                break;
            default:
                cout << "\nInvalid option! Press Enter.";
                cin.get();
        }
    
    }

    l.sessionSummary();

    //Footer Section
    cout << "\nThank you for using Library Management System.\n";

    // End Section of Program
    cout << "\nProgram Ends Here." << endl;
    cout << "Written by \"Hasan B. | @h6nx0\"" << endl;
    cout << "LinkedIn: \"https://www.linkedin.com/in/h6nx0\" | GitHub: \"https://github.com/h6nx0\"" << endl;
    return 0;
}