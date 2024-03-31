#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <unordered_map>

using namespace std;

struct StudentRecord 
{
    string name;
    string studentNum;
    string password;
};

class StudentLoginSystem 
{
public:
    StudentLoginSystem();
    void add_student(const StudentRecord& record);
    bool login(const string& studentNum, const string& password);
    void display_student_records();
public:
    list<StudentRecord> student_records_;
    unordered_map<string, string> login_data_;
};

void StudentLoginSystem::display_student_records() 
{
    cout << "Student Records:\n";
    for (const auto& record : student_records_) {
        cout << "Name: " << record.name << ", Student Number: " << record.studentNum << "\n";
    }
}


StudentLoginSystem::StudentLoginSystem() 
{
    // Add some initial student records
    StudentRecord record1 = {"Juan Dela Cruz", "20211234", "password1"};
    StudentRecord record2 = {"Maria Clara", "20215678", "password2"};
    StudentRecord record3 = {"Crisostomo Ibarra", "20219012", "password3"};
    add_student(record1);
    add_student(record2);
    add_student(record3);
}

void StudentLoginSystem::add_student(const StudentRecord& record) 
{
    student_records_.push_back(record);
    login_data_.insert({record.studentNum, record.password});
}

bool StudentLoginSystem::login(const string& studentNum, const string& password) {
    // Check if the student ID exists in the login data
    auto it = login_data_.find(studentNum);
    if (it == login_data_.end()) 
    {
        cout << "Login failed: Invalid student Credentials.\n";
        return false;
    }
    // Check if the password matches
    if (it->second != password) 
    {
        cout << "Login failed: Incorrect password.\n";
        return false;
    }
    // Find the student record and display it
    auto it2 = student_records_.begin();
    while (it2 != student_records_.end()) 
    {
        if (it2->studentNum == studentNum) {
            cout << "Login successful. Welcome, " << it2->name << ".\n";
            return true;
        }
        it2++;
    }
    return false;
}

void show_main_menu() 
{
    cout << "Welcome to the Student Login System!" << endl;
    cout << "Please choose from the following options:" << endl;
    cout << "1. Login with existing account" << endl;
    cout << "2. Register a new account" << endl;
    cout << "3. Display all student records" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() 
{
    StudentLoginSystem system;

    // Add a new student record
    StudentRecord record4 = {"Jose Rizal", "20210000", "password4"};
    system.add_student(record4);

    char choice;
    do {
        show_main_menu();
        cin >> choice;
        cin.ignore(); // ignore the newline character in the input stream

        if (choice == '1') 
        {
            // Ask the user to login with an existing student record
            string student_num, password;
            cout << "Please enter your student number and password to log in.\n";
            cout << "Student Number: ";
            getline(cin, student_num);
            cout << "Password: ";
            getline(cin, password);

            // Attempt to login with the user's input
            if (system.login(student_num, password)) 
            {
                cout << "Welcome, " << system.student_records_.back().name << ".\n";
            } else 
            {
                cout << "Login failed. Please try again.\n";
            }
        } 
        else if (choice == '2') 
        {
            // Create a new student record
            string name, student_num, password;
            cout << "Enter the new student record information.\n";
            cout << "Name: ";
            getline(cin, name);
            cout << "Student Number: ";
            getline(cin, student_num);
            cout << "Password: ";
            getline(cin, password);

            StudentRecord record = {name, student_num, password};
            system.add_student(record);

            cout << "You have successfully created a new record, " << name << ".\n";

            // Redirect to login
            string new_student_num, new_password;
            cout << "Please enter your student number and password to log in.\n";
            cout << "Student Number: ";
            getline(cin, new_student_num);
            cout << "Password: ";
            getline(cin, new_password);

            if (system.login(new_student_num, new_password)) 
            {
                cout << "Welcome, " << system.student_records_.back().name << ".\n";
            } else 
            {
                cout << "Login failed. Please try again.\n";
            }
        }
        else if (choice == '3') 
        {
            system.display_student_records();
        }
        else if (choice == '4') 
        {
            cout << "Thank you for using the Student Login System. Goodbye!\n";
            break;
        }
        else 
        {
            cout << "Invalid input. Please try again.\n";
        }
    } 
    while (true);

    return 0;
}
