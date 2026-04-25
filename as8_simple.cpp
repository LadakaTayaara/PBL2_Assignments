#include <iostream>
#include <fstream>
using namespace std;

struct Student {
    char name[20];
    int rollno;
    int marks;
};

struct HashEntry {
    int rollno;
    int pos;
};

HashEntry h[10];
int relt = 0;
int s = sizeof(Student);

void initHashTable() {
    for (int i = 0; i < 10; i++) {
        h[i].rollno = -1;
        h[i].pos = -1;
    }
}

void insert_record(bool with_replacement) {
    fstream f("student.txt", ios::binary | ios::app | ios::out);
    Student stud;
    char ch;
    do {
        cout << "Enter student name, rollno, marks: ";
        cin >> stud.name >> stud.rollno >> stud.marks;

        int loc = stud.rollno % 10;
        int curr_roll = stud.rollno;
        int curr_pos = relt;

        // If using Replacement and the home location is occupied by a synonym
        if (with_replacement && h[loc].rollno != -1 && (h[loc].rollno % 10) != loc) {
            curr_roll = h[loc].rollno;     // Demote occupant
            curr_pos = h[loc].pos;
            h[loc].rollno = stud.rollno;   // Place new element at its true home
            h[loc].pos = relt;
        }

        // Linear probing to find the next empty slot for whichever element needs a home
        for (int i = 0; i < 10; i++) {
            int newloc = (loc + i) % 10;
            if (h[newloc].rollno == -1) {
                h[newloc].rollno = curr_roll;
                h[newloc].pos = curr_pos;
                break;
            }
        }

        f.write((char*)&stud, s);
        relt++;

        cout << "Add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    f.close();
}

void create_wor() { insert_record(false); }
void create_wr()  { insert_record(true); }

void display_all() {
    fstream f("student.txt", ios::binary | ios::in);
    Student temp;
    cout << "\nName\t\tRollNo\tMarks\n";
    cout << "--------------------------------\n";
    while (f.read((char*)&temp, s)) {
        cout << temp.name << "\t\t" << temp.rollno << "\t" << temp.marks << "\n";
    }
    f.close();
}

void retrieve() {
    fstream f("student.txt", ios::binary | ios::in);
    Student temp;
    int keyrollno;
    cout << "Enter roll number to search: ";
    cin >> keyrollno;
    bool found = false;
    while (f.read((char*)&temp, s)) {
        if (temp.rollno == keyrollno) {
            cout << "Record found!\n";
            cout << "Name: " << temp.name << "  Roll: " << temp.rollno << "  Marks: " << temp.marks << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Record not found.\n";
    }
    f.close();
}

void modify() {
    fstream f("student.txt", ios::binary | ios::in | ios::out);
    Student temp;
    int keyrollno;
    cout << "Enter roll number to modify: ";
    cin >> keyrollno;
    while (f.read((char*)&temp, s)) {
        if (temp.rollno == keyrollno) {
            cout << "Enter new data (name rollno marks): ";
            cin >> temp.name >> temp.rollno >> temp.marks;
            f.seekp(-s, ios::cur);
            f.write((char*)&temp, s);
            cout << "Record updated.\n";
        }
    }
    f.close();
}

int main() {
    initHashTable();
    int choice;
    do {
        cout << "\n===== Student Database =====";
        cout << "\n1. Create Database (WOR)";
        cout << "\n2. Create Database (WR)";
        cout << "\n3. Display All Records";
        cout << "\n4. Add More Records";
        cout << "\n5. Search Record";
        cout << "\n6. Modify Record";
        cout << "\n7. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: create_wor(); break;
            case 2: create_wr();  break;
            case 3: display_all(); break;
            case 4: create_wor(); break;
            case 5: retrieve();   break;
            case 6: modify();     break;
            case 7: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 7);
    return 0;
}
