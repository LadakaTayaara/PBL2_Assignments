#include <iostream>
using namespace std;

struct Student {
    char name[20];
    int rollno;
    int marks;
};

Student h[10];

void initHashTable() {
    for (int i = 0; i < 10; i++) {
        h[i].rollno = -1;
    }
}

void insert_record(bool with_replacement) {
    Student stud;
    char ch;
    do {
        cout << "Enter student name, rollno, marks: ";
        cin >> stud.name >> stud.rollno >> stud.marks;

        int loc = stud.rollno % 10;
        Student curr_stud = stud;

        // If using Replacement and the home location is occupied by a synonym
        if (with_replacement && h[loc].rollno != -1 && (h[loc].rollno % 10) != loc) {
            curr_stud = h[loc];     // Demote occupant
            h[loc] = stud;          // Place new element at its true home
        }

        // Linear probing to find the next empty slot for whichever element needs a home
        for (int i = 0; i < 10; i++) {
            int newloc = (loc + i) % 10;
            if (h[newloc].rollno == -1) {
                h[newloc] = curr_stud;
                break;
            }
        }

        cout << "Add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

void create_wor() { insert_record(false); }
void create_wr()  { insert_record(true); }

void display_all() {
    cout << "\nName\t\tRollNo\tMarks\n";
    cout << "--------------------------------\n";
    for (int i = 0; i < 10; i++) {
        if (h[i].rollno != -1) {
            cout << h[i].name << "\t\t" << h[i].rollno << "\t" << h[i].marks << "\n";
        }
    }
}

void retrieve() {
    int keyrollno;
    cout << "Enter roll number to search: ";
    cin >> keyrollno;
    
    int loc = keyrollno % 10;
    for (int i = 0; i < 10; i++) {
        int newloc = (loc + i) % 10;
        if (h[newloc].rollno == keyrollno) {
            cout << "Record found!\n";
            cout << "Name: " << h[newloc].name << "  Roll: " << h[newloc].rollno << "  Marks: " << h[newloc].marks << "\n";
            return;
        }
        if (h[newloc].rollno == -1) break; // Optimization: Stop searching if empty slot found
    }
    cout << "Record not found.\n";
}

void modify() {
    int keyrollno;
    cout << "Enter roll number to modify: ";
    cin >> keyrollno;

    int loc = keyrollno % 10;
    for (int i = 0; i < 10; i++) {
        int newloc = (loc + i) % 10;
        if (h[newloc].rollno == keyrollno) {
            cout << "Enter new data (name rollno marks): ";
            cin >> h[newloc].name >> h[newloc].rollno >> h[newloc].marks;
            cout << "Record updated.\n";
            return;
        }
        if (h[newloc].rollno == -1) break; 
    }
    cout << "Record not found.\n";
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
