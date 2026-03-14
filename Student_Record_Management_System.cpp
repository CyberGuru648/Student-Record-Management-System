#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <iomanip>
using namespace std;

struct student
{
    string name;
    int roll;
    int marks;
};

bool check_duplicate(int roll)
{
    student s;
    ifstream fin("student.txt");

    if (!fin)
    {
        return false;
    }

    while (getline(fin, s.name))
    {
        fin >> s.roll;
        fin >> s.marks;
        fin.ignore();

        if (s.roll == roll)
        {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}
void add_student()
{

    student s;
    ofstream fout("student.txt", ios::app);

    // ifstream fin("student.txt");

    cout << "Enter roll : ";
    cin >> s.roll;
    if (check_duplicate(s.roll))
    {
        cout << "Student already exists : " << endl;
    }
    else

    {
        cin.ignore();
        cout << "Enter Name : ";
        getline(cin, s.name);

        cout << "Enter Marks : ";
        cin >> s.marks;

        fout << s.name << endl;
        fout << s.roll << endl;
        fout << s.marks << endl;
        cout << ".... Student Added Successfully .....\n";
    }
    fout.close();
}

void line()
{
    cout << "-----------------------------------------------\n";
}
void display()
{
    student s;
    ifstream fin("student.txt");

    if (!fin)
    {
        cout << "File not found\n";
        return;
    }

    // cout << "\t\t\tName\t\tRoll\tMarks\n";

    line();
    cout << "| " << left << setw(20) << "Name"
         << "| " << setw(10) << "Roll"
         << "| " << setw(10) << "Marks"
         << "|\n";

    line();

    while (getline(fin, s.name))
    {
        fin >> s.roll;
        fin >> s.marks;
        fin.ignore();
        // cout << "\n\t\t\t" << s.name << "\t" << s.roll << "\t" << s.marks << endl;
        cout << "| " << left << setw(20) << s.name
             << "| " << setw(10) << s.roll
             << "| " << setw(10) << s.marks
             << "| \n";
    }
    line();

    fin.close();
}

void search_student()
{
    student s;
    int search;
    bool found = false;

    cout << "Enter Roll Number : ";
    cin >> search;

    ifstream fin("student.txt");

    if (!fin)
    {
        cout << "File not found\n";
        return;
    }

    while (getline(fin, s.name))
    {
        fin >> s.roll;
        fin >> s.marks;
        fin.ignore();

        if (s.roll == search)
        {
            cout << "Student Found \n";
            cout << "Name : " << s.name << endl;
            cout << "Marks : " << s.marks << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Student Not Found \n";
    }
    fin.close();
}

void find_topper()
{
    student s;
    ifstream fin("student.txt");

    if (!fin)
    {
        cout << "File not found\n";
        return;
    }

    int maxMarks = -1;
    student topper;

    while (getline(fin, s.name))
    {
        fin >> s.roll;
        fin >> s.marks;
        fin.ignore();
        if (s.marks > maxMarks)
        {
            maxMarks = s.marks;
            topper = s;
        }
    }
    if (maxMarks != -1)
    {
        cout << "\nTopper\n";
        cout << "Name : " << topper.name << endl;
        cout << "Roll : " << topper.roll << endl;
        cout << "Marks : " << topper.marks << endl;
    }
    else
        cout << "No Data Found \n";

    fin.close();
}

void delete_student()
{
    student s;
    int del_roll;
    bool found = false;
    ifstream fin("student.txt");

    if (!fin)
    {
        cout << "File not found\n";
        return;
    }

    ofstream fout("temp.txt");

    if (!fin || !fout)
    {
        cout << "File not found\n";
        return;
    }
    cout << "Enter Roll Number To Delete : ";
    cin >> del_roll;
    while (getline(fin, s.name))
    {
        fin >> s.roll;
        fin >> s.marks;
        fin.ignore();

        if (s.roll == del_roll)
        {
            found = true;
            continue;
        }
        else
        {
            fout << s.name << endl;
            fout << s.roll << endl;
            fout << s.marks << endl;
        }
    }

    fin.close();
    fout.close();

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found == true)
    {
        cout << "Student Data Deleted ....." << endl;
    }
    else
        cout << "Student Data Not Found ....";
}

void update_marks()
{
    student s;
    bool found = false;
    int new_roll;
    ifstream fin("student.txt");
    ofstream fout("temp.txt");

    if (!fin || !fout)
    {
        cout << "File does not exist \n";
        return;
    }

    cout << "Enter roll number : ";
    cin >> new_roll;

    while (getline(fin, s.name))
    {
        fin >> s.roll;
        fin >> s.marks;
        fin.ignore();

        if (s.roll == new_roll)
        {
            found = true;
            cout << "Enter Your Marks ";
            cin >> s.marks;

            fout << s.name << endl;
            fout << s.roll << endl;
            fout << s.marks << endl;
        }
        else
        {
            fout << s.name << endl;
            fout << s.roll << endl;
            fout << s.marks << endl;
        }
    }

    fin.close();
    fout.close();
    remove("student.txt");
    rename("temp.txt", "student.txt");
    if (found)
        cout << "Student Marks Updated : " << endl;
    else
        cout << "No record found : " << endl;
}
int main()
{
    int choice;

    cout << "\n--------  WELCOME TO STUDENT RECORD MANAGEMENT SYSTEM  ---------------\n"
         << endl;
    cout << "1. Add Student \n";
    cout << "2. Display Student \n";
    cout << "3. Search Student \n";
    cout << "4. Find Topper \n";
    cout << "5. Delete Student \n";
    cout << "6. Update Student Marks \n";
    cout << "0. Exit \n";
    do
    {
        cout << "Enter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_student();
            break;
        case 2:
            display();
            break;
        case 3:
            search_student();
            break;
        case 4:
            find_topper();
            break;
        case 5:
            delete_student();
            break;
        case 6:
            update_marks();
            break;
        }
    } while (choice != 0);

    return 0;
}