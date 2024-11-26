#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX_STUDENTS = 20;
const int MAX_BOOKS = 15;
const int MAX_NAME_LENGTH = 50;

int student_count = 0;
int book_count = 0;
double student_balance[MAX_STUDENTS];
int student_roll[MAX_STUDENTS];
char student_name[MAX_STUDENTS][MAX_NAME_LENGTH];
char book_title[MAX_BOOKS][MAX_NAME_LENGTH];
char book_author[MAX_BOOKS][MAX_NAME_LENGTH];
int book_isbn[MAX_BOOKS];
bool book_available[MAX_BOOKS];


void create_account();
void display(int roll);
void deposit_amount(int roll, double amount);
void issue_item(int roll);
void display_sorted();
int find_student(int roll);
int find_book(int isbn);
void add_book();
void edit_book();
void view_books();
void initialize_books();

int main()
{
    initialize_books();

    const char *student_names[MAX_STUDENTS] = {
        "Aryan", "Bassi", "Charlie", "Deepak", "Eshu", "Farhan", "Gaurabh", "Hardik",
        "Ishika", "Jolly", "Karan", "Laksh", "Mahi", "Nishu", "Oshank", "Prateek", "Queen",
        "Rohan", "Sanju", "Taruna"};

    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        student_roll[i] = 10001 + i;
        strcpy(student_name[i], student_names[i]);
        student_balance[i] = 50; 
    }
    student_count = MAX_STUDENTS;

    int option;
    bool is_admin;
    string password;

    while (true)
    {
        cout << "Login as:\n1. Admin\n2. Student\n0. Exit\n";
        cin >> option;

        if (option == 0)
        {
            break;
        }

        is_admin = (option == 1);

        cout << "Enter password: ";
        cin >> password;

        if (password == "password")
        {
            if (is_admin)
            {
                cout << "Admin options:\n1. Add book\n2. Edit book\n3. View book status\n4. View enrolled students\n5. View student balance\n";
                cin >> option;

                switch (option)
                {
                case 1:
                    add_book();
                    break;
                case 2:
                    edit_book();
                    break;
                case 3:
                    view_books();
                    break;
                case 4:
                    display_sorted();
                    break;
                case 5:
                {
                    int roll;
                    cout << "Enter student roll number: ";
                    cin >> roll;
                    display(roll);
                    break;
                }
                }
            }
            else
            {
                int roll;
                cout << "Enter your roll number: ";
                cin >> roll;

                int index = find_student(roll);
                if (index == -1)
                {
                    cout << "Student not found. Create an account? (1. Yes / 2. No): ";
                    cin >> option;
                    if (option == 1)
                    {
                        create_account();
                    }
                }
                else
                {
                    cout << "Student options:\n1. View balance\n2. Deposit amount\n3. Issue item\n";
                    cin >> option;

                    switch (option)
                    {
                    case 1:
                        display(roll);
                        break;
                    case 2:
                    {
                        double amount;
                        cout << "Enter the amount to deposit: ";
                        cin >> amount;
                        deposit_amount(roll, amount);
                        break;
                    }
                    case 3:
                        issue_item(roll);
                        break;
                    }
                }
            }
        }
        else
        {
            cout << "Incorrect password.\n";
        }
    }
    return 0;
}

void initialize_books()
{
    const char *titles[MAX_BOOKS] = {
        "To Kill a Mockingbird", "1984", "The Great Gatsby", "The Catcher in the Rye", "The Hobbit",
        "Fahrenheit 451", "Moby-Dick", "Pride and Prejudice", "War and Peace", "The Odyssey",
        "Crime and Punishment", "The Lord of the Rings", "Jane Eyre", "Brave New World", "Wuthering Heights"};

    const char *authors[MAX_BOOKS] = {
        "Harper Lee", "George Orwell", "F. Scott Fitzgerald", "J.D. Salinger", "J.R.R. Tolkien",
        "Ray Bradbury", "Herman Melville", "Jane Austen", "Leo Tolstoy", "Homer",
        "Fyodor Dostoevsky", "J.R.R. Tolkien", "Charlotte Bronte", "Aldous Huxley", "Emily Bronte"};

    int isbns[MAX_BOOKS] = {978006, 978045, 978074, 978031, 978034, 978145, 978150, 978014, 978185, 978019,
                            978067, 978039, 978055, 978006, 978014};

    for (int i = 0; i < MAX_BOOKS; i++)
    {
        strcpy(book_title[i], titles[i]);
        strcpy(book_author[i], authors[i]);
        book_isbn[i] = isbns[i];
        book_available[i] = true;
    }
    book_count = MAX_BOOKS;
}

void create_account()
{
    if (student_count >= MAX_STUDENTS)
    {
        cout << "Student limit reached. Cannot create more accounts.\n";
        return;
    }

    int roll;
    cout << "Enter roll number: ";
    cin >> roll;

    if (find_student(roll) != -1)
    {
        cout << "Account already exists for this roll number.\n";
        return;
    }

    student_roll[student_count] = roll;
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(student_name[student_count], MAX_NAME_LENGTH);

    double initial_deposit;
    cout << "Enter initial deposit amount ($50 minimum): ";
    cin >> initial_deposit;

    if (initial_deposit < 50)
    {
        cout << "Initial deposit must be at least $50.\n";
        return;
    }

    student_balance[student_count] = initial_deposit - 50;
    student_count++;
}

void display(int roll)
{
    int index = find_student(roll);
    if (index == -1)
    {
        cout << "Student not found.\n";
        return;
    }

    cout << "Roll No: " << student_roll[index] << endl;
    cout << "Name: " << student_name[index] << endl;
    cout << "Balance: $" << fixed << setprecision(2) << student_balance[index] << endl;
}

void deposit_amount(int roll, double amount)
{
    int index = find_student(roll);
    if (index == -1)
    {
        cout << "Student not found.\n";
        return;
    }

    student_balance[index] += amount;
    cout << "New balance: $" << fixed << setprecision(2) << student_balance[index] << endl;
}

void issue_item(int roll)
{
    int index = find_student(roll);
    if (index == -1)
    {
        cout << "Student not found.\n";
        return;
    }

    cout << "Available books:\n";
    for (int i = 0; i < book_count; i++)
    {
        if (book_available[i])
        {
            cout << i + 1 << ". " << book_title[i] << " by " << book_author[i] << " (ISBN: " << book_isbn[i] << ")\n";
        }
    }

    int choice;
    cout << "Enter the number of the book you want to issue (0 to cancel): ";
    cin >> choice;

    if (choice == 0)
    {
        return;
    }

    if (book_available[choice - 1] && student_balance[index] >= 2)
    {
        book_available[choice - 1] = false;
        student_balance[index] -= 2;
        cout << "Book issued successfully. New balance: $" << fixed << setprecision(2) << student_balance[index] << endl;
    }
    else
    {
        cout << "Cannot issue the book. Insufficient balance or book is unavailable.\n";
    }
}

void display_sorted()
{
    for (int i = 0; i < student_count; i++)
    {
        for (int j = i + 1; j < student_count; j++)
        {
            if (strcmp(student_name[i], student_name[j]) > 0)
            {
                swap(student_roll[i], student_roll[j]);
                swap(student_balance[i], student_balance[j]);
                char temp[MAX_NAME_LENGTH];
                strcpy(temp, student_name[i]);
                strcpy(student_name[i], student_name[j]);
                strcpy(student_name[j], temp);
            }
        }
    }

    cout << "Sorted list of students:\n";
    for (int i = 0; i < student_count; i++)
    {
        cout << "Roll No: " << student_roll[i] << ", Name: " << student_name[i] << ", Balance: $" << fixed << setprecision(2) << student_balance[i] << endl;
    }
}

int find_student(int roll)
{
    for (int i = 0; i < student_count; i++)
    {
        if (student_roll[i] == roll)
        {
            return i;
        }
    }
    return -1;
}

void add_book()
{
    if (book_count >= MAX_BOOKS)
    {
        cout << "Book limit reached. Cannot add more books.\n";
        return;
    }

    cout << "Enter book title: ";
    cin.ignore();
    cin.getline(book_title[book_count], MAX_NAME_LENGTH);
    cout << "Enter book author: ";
    cin.getline(book_author[book_count], MAX_NAME_LENGTH);
    cout << "Enter book ISBN: ";
    cin >> book_isbn[book_count];

    book_available[book_count] = true;
    book_count++;
    cout << "Book added successfully.\n";
}

void edit_book()
{
    int isbn;
    cout << "Enter ISBN of the book to edit: ";
    cin >> isbn;

    int index = find_book(isbn);
    if (index == -1)
    {
        cout << "Book not found.\n";
        return;
    }

    cout << "Editing book: " << book_title[index] << " by " << book_author[index] << endl;
    cout << "Enter new title (or press Enter to keep current): ";
    cin.ignore();
    cin.getline(book_title[index], MAX_NAME_LENGTH);
    cout << "Enter new author (or press Enter to keep current): ";
    cin.getline(book_author[index], MAX_NAME_LENGTH);
    cout << "Is the book available? (1. Yes / 2. No): ";
    int choice;
    cin >> choice;
    book_available[index] = (choice == 1);

    cout << "Book updated successfully.\n";
}

void view_books()
{
    cout << "Books in the library:\n";
    for (int i = 0; i < book_count; i++)
    {
        cout << i + 1 << ". " << book_title[i] << " by " << book_author[i] << " (ISBN: " << book_isbn[i] << ")"
             << (book_available[i] ? " [Available]" : " [Not Available]") << endl;
    }
}

int find_book(int isbn)
{
    for (int i = 0; i < book_count; i++)
    {
        if (book_isbn[i] == isbn)
        {
            return i;
        }
    }
    return -1;
}
