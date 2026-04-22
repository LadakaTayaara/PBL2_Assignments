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

void create_wor() {
    fstream f("student.txt", ios::binary | ios::app | ios::out);
    Student stud;
    char ch;
    do {
        cout << "Enter student name, rollno, marks: ";
        cin >> stud.name >> stud.rollno >> stud.marks;

        int loc = stud.rollno % 10;

        if (h[loc].rollno == -1) {
            h[loc].rollno = stud.rollno;
            h[loc].pos = relt;
        } else {
            for (int i = 1; i < 10; i++) {
                int newloc = (loc + i) % 10;
                if (h[newloc].rollno == -1) {
                    h[newloc].rollno = stud.rollno;
                    h[newloc].pos = relt;
                    break;
                }
            }
        }

        f.write((char*)&stud, s);
        relt++;

        cout << "Add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    f.close();
}

void create_wr() {
    fstream f("student.txt", ios::binary | ios::app | ios::out);
    Student stud;
    char ch;
    do {
        cout << "Enter student name, rollno, marks: ";
        cin >> stud.name >> stud.rollno >> stud.marks;

        int loc = stud.rollno % 10;

        if (h[loc].rollno == -1) {
            h[loc].rollno = stud.rollno;
            h[loc].pos = relt;
        } else {
            int home_of_occupant = h[loc].rollno % 10;

            if (home_of_occupant == loc) {
                for (int i = 1; i < 10; i++) {
                    int newloc = (loc + i) % 10;
                    if (h[newloc].rollno == -1) {
                        h[newloc].rollno = stud.rollno;
                        h[newloc].pos = relt;
                        break;
                    }
                }
            } else {
                int temp_rollno = h[loc].rollno;
                int temp_pos = h[loc].pos;

                h[loc].rollno = stud.rollno;
                h[loc].pos = relt;

                for (int i = 1; i < 10; i++) {
                    int newloc = (loc + i) % 10;
                    if (h[newloc].rollno == -1) {
                        h[newloc].rollno = temp_rollno;
                        h[newloc].pos = temp_pos;
                        break;
                    }
                }
            }
        }

        f.write((char*)&stud, s);
        relt++;

        cout << "Add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    f.close();
}

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
