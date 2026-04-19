#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

class student{
    public:
    char name[20];
    int rollno;
    int marks;
    
    friend class records;
};

class hashing{
    public:
    int rollno;
    int pos;
    
    hashing(){
        rollno=-1;
        pos=-1;
        }
        
    friend class records;
};

class records {
    public:
    student stud;
    hashing h[10];
    int relt,s;
    
    records();
    void create_wor();
    void create_wr();
    void display_all();
    void retrieve();
    void modify();
};

records :: records(){
    s=sizeof(student);
    relt=0;
    
    for(int i=0; i<10; i++){
        h[i].rollno=-1;
        h[i].pos=-1;
    }
}

void records :: create_wor(){
    
    fstream f("student.txt", ios::binary | ios::app | ios::out);
    char ch;
    int loc;
    do{
        cout << "enter student name, rollno, marks\n";
        cin >> stud.name >> stud.rollno >> stud.marks;
        
        loc=(stud.rollno)%10;
        
        if(h[loc].rollno==-1){
            h[loc].rollno=stud.rollno;
            h[loc].pos=relt;
        }else{
            for(int i=1; i<10; i++){
                int newloc=(loc+i)%10;
                
                if(h[newloc].rollno==-1){
                    h[newloc].rollno=stud.rollno;
                    h[newloc].pos=relt;
                    break;
                }
            }
        }
        
        f.write((char*)&stud,s);
        relt++;  
        
        cout << "do you wanna add more records? \n";
        cin >> ch;
    }while(ch=='y'|| ch=='Y');
    
    f.close();
}


void records :: create_wr(){
    
    fstream f("student.txt", ios::binary | ios::app | ios::out);
    char ch;
    int loc;
    do{
        cout << "enter student name, rollno, marks\n";
        cin >> stud.name >> stud.rollno >> stud.marks;
        
        loc=(stud.rollno)%10;
        
        if(h[loc].rollno==-1){
            h[loc].rollno=stud.rollno;
            h[loc].pos=relt;
        }else{
            
            int home_occupant = (h[loc].rollno)%10;
            
            if(home_occupant==loc){
                
                for(int i=1; i<10; i++){
                int newloc=(loc+i)%10;
                
                if(h[newloc].rollno==-1){
                    h[newloc].rollno=stud.rollno;
                    h[newloc].pos=relt;
                    break;
                }
              }
            }else{
                
                int temp_rollno= h[loc].rollno;
                int temp_pos=h[loc].pos;
                
                h[loc].rollno= stud.rollno;
                h[loc].pos= relt;
                
                for(int i=1; i<10; i++){
                int newloc=(loc+i)%10;
                
                if(h[newloc].rollno==-1){
                    h[newloc].rollno=temp_rollno;
                    h[newloc].pos=temp_pos;
                    break;
                }
              }
            }
        }

        f.write((char*)&stud,s);   
        relt++;                   
        
        cout << "do you wanna add more records? \n";
        cin >> ch;               
        
    }while(ch=='Y'|| ch=='y');
    
    f.close();
}

void records :: display_all (){
    
    fstream f("student.txt" ,ios::binary | ios::in);
    student temp;
    
    cout << "name\t rollno\t marks\n";
    while(f.read((char*)&temp,s))
        {
            cout << temp.name << "\t" << temp.rollno << "\t" << temp.marks << endl; 
        }
        
    f.close();
}

void records :: retrieve (){
    
    fstream f("student.txt" ,ios::binary | ios::in);
    student temp;
    
    int keyrollno;
    cout << "enter rollno to search : ";
    cin >> keyrollno;
    
    bool found =false;
    
    while(f.read((char*)&temp ,s)){
        if(temp.rollno==keyrollno){
            cout << "record found\n";
            cout << temp.name << "\t" << temp.rollno << "\t" << temp.marks <<endl;
            found=true;
            break;
        }
    }
    
    if(!found){
        cout << "record not found\n";
    }
    
    f.close();
}

void records :: modify (){
    
    fstream f("student.txt" , ios::binary | ios::in | ios::out);
    student temp;
    
    int keyrollno;
    cout << "enter rollno to modify\n";
    cin >> keyrollno;
    
    while(f.read((char*)&temp ,s)){
        if(temp.rollno==keyrollno){
            cout << "enter new data (name ,rollno, marks) : ";
            cin >> temp.name >> temp.rollno >> temp.marks;
            
            f.seekp(-s, ios::cur);
            f.write((char*)&temp, s);
        }
    }
    f.close();
}

int main (){
    
    records r;
    
    int choice;

    do
    {
        cout << "\n1. Create Student Database (WOR)";
        cout << "\n2. Create Student Database (WR)";
        cout << "\n3. Display Database";
        cout << "\n4. Add Record";
        cout << "\n5. Search Record";
        cout << "\n6. Modify Record";
        cout << "\n7. Exit";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            r.create_wor();
            break;

        case 2:
            r.create_wr();
            break;

        case 3:
            r.display_all();
            break;

        case 4:
            r.create_wor();
            break;

        case 5:
            r.retrieve();
            break;

        case 6:
            r.modify();
            break;

        case 7:
            return 0;
        }

    } while (choice != 7);
    
    return 0;
}