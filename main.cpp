#include <iostream>

using namespace std;

//book node .. both book and copy

struct book
{
    string bookName;
    int bookISBN;
    int numOfCopies;
    book *prCopies;
    book *next;
    string copyDate;
    string borrowed;
    string borrower;
    string borrowDate;
    int numOfDays ;
    book *nextCopy;
    int available;
};

class library
{
    book *head;
    book *tail;
    book *headCopy;
    book *tailCopy;
    int bookLength;
    int borrowedBooks;

public:

    //constructor
    library()
    {
        head = tail = headCopy = tailCopy =  NULL;
        bookLength = borrowedBooks = 0;
    }

    //function to add a new book
    void addBook (string name, int ISBN)
    {
        if(bookLength == 0) //if there isn't any book
        {
            book* newBook = new book;
            newBook->bookName = name;
            newBook->bookISBN = ISBN;
            newBook->available = 0;
            newBook->numOfCopies = 0;
            head = tail = newBook;
            newBook->next = NULL;
            bookLength++;
        }
        else //if there are books
        {
            book* newBook = new book;
            newBook->bookName = name;
            newBook->bookISBN = ISBN;
            newBook->available = 0;
            newBook->numOfCopies = 0;
            tail->next = newBook;
            newBook->next = NULL;
            tail = newBook;
            bookLength++;
        }

    }

    //function to search about a specific book by book ISBN
    void search(int ISBN)
    {
        book *current = head;
        while(current != NULL)
        {
            if(current->bookISBN == ISBN)
            {
                if(current->available != 0 && current->numOfCopies != 0)
                {
                    cout<<"Book : "<<current->bookName<<" has "<<current->available<<" copy in this moment"<<endl;
                }
                else
                {
                    cout<<"Book : "<<current->bookName<<" has 0 copies in this moment"<<endl;
                }
            }
            current = current->next;

        }
    }

    //function to add a copy to a specific book by book ISBN
    void addCopy(string copyDate , string borrowed , string borrower, string borrowDate , int numOfDays , int bookISBN)
    {

            book *newCopy = new book;
            newCopy->copyDate = copyDate;
            newCopy->borrowed = borrowed;
            newCopy->borrower = borrower;
            newCopy->borrowDate = borrowDate;
            newCopy->numOfDays = numOfDays;
            book *current = head;
            while (current != NULL)
            {
                if (current->bookISBN == bookISBN)
                {
                    if(current->numOfCopies == 0)
                    {
                        headCopy = tailCopy = newCopy;
                        newCopy->nextCopy = NULL;
                        current->prCopies = newCopy;
                        current->numOfCopies++;
                        if(borrowed == "available") //to set the number of available copies to borrow
                        {
                            current->available++;
                        }
                    }
                    else
                    {
                        tailCopy->nextCopy = newCopy;
                        newCopy->nextCopy = NULL;
                        tailCopy = newCopy;
                        current->numOfCopies++;
                        if(borrowed == "available") //to set the number of available copies to borrow
                        {
                            current->available++;
                        }
                    }
                }
                current = current->next;
            }
    }

    //function to show the copies and all the numbers belongs to a specific book by book ISBN
    void inventory(int bookISBN)
    {
        book *current = head;
        book *firstCopy = headCopy;
        int num =1;
        while (current != NULL)
        {
            if(current->bookISBN == bookISBN)
            {
                current->prCopies = firstCopy;
                cout<<"Book name : "<<current->bookName<<" has "<<current->numOfCopies<<" copy : "<<endl;
                cout<<"Available : "<<current->available<<endl;
                cout<<"Borrowed : "<<(current->numOfCopies)-(current->available)<<endl;
                while (firstCopy != NULL)
                {
                    cout<<num<<" - copy date : "<<firstCopy->copyDate<<",  "<<firstCopy->borrowed<<", borrower : "<<firstCopy->borrower<<", borrow date : "<<firstCopy->borrowDate<<", num of days to return : "<<firstCopy->numOfDays<<" "<<endl;
                    firstCopy = firstCopy->nextCopy;
                    num++;
                }

           }
            current = current->next;

        }
        cout<<endl;
    }

    // bool function to return if the book is in the library or not
    bool checkIfFound(int bookISBN)
    {
        book *Cur = head;
        int done = 0;
        while(Cur != NULL)
        {
            if(Cur->bookISBN == bookISBN)
            {

                return true;
            }
            Cur = Cur->next;
        }
        if(done == 0)
        {
            return false;
        }
    }

    //function to borrow book
    void borrowBook(string borrower , int bookISBN , string borrowDate , int numOfDays)
    {
        book *current = head;
        book *firstCopy = headCopy;
        int found = 0;
        while(current != NULL  )
        {
            if(current->bookISBN == bookISBN && current->available != 0 && current->numOfCopies != 0)
            {
                current->prCopies = firstCopy;
                while (firstCopy != NULL)
                {
                    if (firstCopy->borrowed == "available")
                    {
                        firstCopy->borrowed = "borrowed";
                        firstCopy->borrower = borrower;
                        firstCopy->borrowDate = borrowDate;
                        firstCopy->numOfDays = numOfDays;
                        current->available--;
                        cout<<"You have borrowed a book, and you have "<<numOfDays<<" to return it"<<endl;
                        found++;
                        borrowedBooks++;
                        break;
                    }
                    firstCopy = firstCopy->nextCopy;
                }
            }

            current = current->next;
        }
        if(found == 0)
        {
            cout<<"There isn't available copies of this book ! "<<endl;
        }

    }

    //function to return book
    void returnBook(string borrower , int bookISBN , string borrowDate )
    {
        book *current = head;
        book *firstCopy = headCopy;
        int found = 0;
        while(current != NULL  )
        {
            if(current->bookISBN == bookISBN  && current->numOfCopies != 0)
            {
                current->prCopies = firstCopy;
                while (firstCopy != NULL)
                {
                    if (firstCopy->borrowed == "borrowed" && firstCopy->borrowDate == borrowDate && firstCopy->borrower == borrower )
                    {
                        firstCopy->borrowed = "available";
                        firstCopy->borrower = " ";
                        firstCopy->borrowDate = " ";
                        firstCopy->numOfDays = 0;
                        current->available++;
                        cout<<"You have return your copy successfully "<<endl;
                        borrowedBooks--;
                        found++;
                        break;
                    }
                    firstCopy = firstCopy->nextCopy;
                }
            }

            current = current->next;
        }
        if(found == 0)
        {
            cout<<"Your borrowed copy doesn't exist in this moment !"<<endl;
        }

    }

    //function to show the total number of borrowed books in the library
    void showBorrowStat()
    {
        cout<<"There are : "<<borrowedBooks<<" borrowed book "<<endl;
    }

};

int main()
{
    cout<<"*******Welcome to Library Management System******* "<<endl;
    cout<<"Main Menu : "<<endl;
    cout<<"Choose one from below : "<<endl;
    library l;
    int choice;
    char again;
    main:
    {
        cout<<" 1- Add a new book \n 2- Add a book copy \n 3- Borrow a book \n 4- Return a book \n 5- Show borrow statistics \n 6- Library inventory \n 7- Search about book "<<endl;
        cin>>choice;
        if(choice == 1)
        {
            string bookName ;
            int bookISBN ;
            cout<<"Enter the name of the book "<<endl;
            cin>>bookName;
            cout<<"Enter the ISBN of the book "<<endl;
            cin>>bookISBN;

            l.addBook(bookName, bookISBN);
            cout<<"You have successfully added a new book "<<endl;
            cout<<"Press 'b' to back to the main menu"<<endl;
            cin>>again;
            if(again == 'b')
            {
                goto main;
            }

        }
        else if(choice == 2)
        {
            string copyDate , borrowed , borrower  , borrowDate ;
            int bookISBN , numOfDays ;
            cout<<"Enter the ISBN of the book "<<endl;
            cin>>bookISBN;
            if(l.checkIfFound(bookISBN))
            {
                cout<<"Enter the copy date of the book "<<endl;
                cin>>copyDate;
                borrowed:
                {
                    cout<<"Enter witch the book is 'available' or 'borrowed' "<<endl;
                    cin>>borrowed;
                    if(borrowed != "available" && borrowed != "borrowed")
                    {
                        cout<<"Invalid input! "<<endl;
                        goto borrowed;
                    }
                    if(borrowed == "available")
                    {
                        borrower = " - ";
                        borrowDate = " - ";
                        numOfDays = 15;
                        l.addCopy(copyDate , borrowed , borrower , borrowDate ,numOfDays, bookISBN);
                        cout<<"You have successfully added a new copy "<<endl;
                        cout<<"Press 'b' to back to the main menu"<<endl;
                        cin>>again;
                        if(again == 'b')
                        {
                            goto main;
                        }
                    }
                    else if(borrowed == "borrowed")
                    {
                        cout<<"Enter the borrower of the book "<<endl;
                        cin>>borrower;
                        cout<<"Enter the borrowDate of the book "<<endl;
                        cin>>borrowDate;
                        cout<<"Enter the number of days to return the book  "<<endl;
                        cin>>numOfDays;
                        l.addCopy(copyDate , borrowed , borrower , borrowDate ,numOfDays, bookISBN);
                        cout<<"You have successfully added a new copy "<<endl;
                        cout<<"Press 'b' to back to the main menu"<<endl;
                        cin>>again;
                        if(again == 'b')
                        {
                            goto main;
                        }
                    }

            }
            }
            else
            {
                cout<<"This book is not found !"<<endl;
                cout<<"Press 'b' to back to the main menu"<<endl;
                cin>>again;
                if(again == 'b')
                {
                    goto main;
                }
            }

        }
        else if(choice == 3)
        {
            string borrower , borrowDate;
            int bookISBN , numOfDays;
            cout<<"Enter borrower name "<<endl;
            cin>>borrower;
            cout<<"Enter the ISBN of the book "<<endl;
            cin>>bookISBN;
            if(l.checkIfFound(bookISBN))
            {
                cout<<"Enter the borrowDate of the book "<<endl;
                cin>>borrowDate;
                cout<<"Enter the number of days to return the book  "<<endl;
                cin>>numOfDays;
                l.borrowBook( borrower ,  bookISBN ,  borrowDate ,  numOfDays);
                cout<<"Press 'b' to back to the main menu"<<endl;
                cin>>again;
                if(again == 'b')
                {
                    goto main;
                }
            }
            else
            {
                cout<<"This book is not found !"<<endl;
                cout<<"Press 'b' to back to the main menu"<<endl;
                cin>>again;
                if(again == 'b')
                {
                    goto main;
                }
            }

        }
        else if(choice == 4)
        {
            string borrower , borrowDate;
            int bookISBN;
            cout<<"Enter your name "<<endl;
            cin>>borrower;
            cout<<"Enter the ISBN of the book "<<endl;
            cin>>bookISBN;
            if(l.checkIfFound(bookISBN))
            {
                cout<<"Enter the borrowDate of the book "<<endl;
                cin>>borrowDate;
                l.returnBook(borrower , bookISBN , borrowDate);
                cout<<"Press 'b' to back to the main menu"<<endl;
                cin>>again;
                if(again == 'b')
                {
                    goto main;
                }
            }
            else
            {
                cout<<"This book is not found !"<<endl;
                cout<<"Press 'b' to back to the main menu"<<endl;
                cin>>again;
                if(again == 'b')
                {
                    goto main;
                }
            }

        }
        else if(choice == 5)
        {
            l.showBorrowStat();
            cout<<"Press 'b' to back to the main menu"<<endl;
            cin>>again;
            if(again == 'b')
            {
                goto main;
            }

        }
        else if(choice == 6)
        {
            int bookISBN;
           cout<<"Enter the ISBN of the book you want to show the copies of it "<<endl;
           cin>>bookISBN;
            if(l.checkIfFound(bookISBN))
            {
                l.inventory(bookISBN);
                cout<<"Press 'b' to back to the main menu"<<endl;
                cin>>again;
                if(again == 'b')
                {
                    goto main;
                }
            }
            else
            {
                cout<<"This book is not found !"<<endl;
                cout<<"Press 'b' to back to the main menu"<<endl;
                cin>>again;
                if(again == 'b')
                {
                    goto main;
                }
            }
        }
        else if(choice == 7)
        {
            int bookISBN ;
            cout<<"Enter the ISBN of the book "<<endl;
            cin>>bookISBN;
            if(l.checkIfFound(bookISBN))
            {
                l.search(bookISBN);
                cout<<"Press 'b' to back to the main menu"<<endl;
                cin>>again;
                if(again == 'b')
                {
                    goto main;
                }
            }
            else
            {
                cout<<"This book is not found !"<<endl;
                cout<<"Press 'b' to back to the main menu"<<endl;
                cin>>again;
                if(again == 'b')
                {
                    goto main;
                }
            }
        }

        else
        {
            cout<<"Invalid input .. Please try again !"<<endl;
            goto main;
        }
    }
    return 0;
}
