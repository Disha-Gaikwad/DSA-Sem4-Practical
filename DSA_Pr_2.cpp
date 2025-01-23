#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class student {
    typedef struct stud {
        int roll;
        char name[10];
        char div;
        char add[10];
    } stud;
    stud rec;

public:
    void create();
    void display();
    int search();
    void Delete();
};

void student::create() {
    char ans;
    ofstream fout;
    fout.open("stud.dat", ios::out | ios::binary);
    
    do {
        cout << "\n\tEnter Roll No of Student: ";
        cin >> rec.roll;
        cout << "\n\tEnter Name of Student: ";
        cin >> rec.name;
        cout << "\n\tEnter Division of Student: ";
        cin >> rec.div;
        cout << "\n\tEnter Address of Student: ";
        cin >> rec.add;

        fout.write((char*)&rec, sizeof(stud)); 
        fout.flush();
        
        cout << "\n\tDo You Want to Add More Records? (y/n): ";
        cin >> ans;
    } while(ans == 'y' || ans == 'Y');

    fout.close();
}

void student::display() {
    ifstream fin;
    fin.open("stud.dat", ios::in | ios::binary); 

    if (!fin) {
        cout << "\n\tError opening file!";
        return;
    }

    fin.seekg(0, ios::beg);
    cout << "\n\tThe Content of File are:\n";
    cout << "\n\tRoll\tName\tDiv\tAddress\n";

    while(fin.read((char*)&rec, sizeof(stud))) {
        if(rec.roll != -1) {  // Record exists (not deleted)
            cout << "\n\t" << rec.roll << "\t" << rec.name << "\t" << rec.div << "\t" << rec.add;
        }
    }

    fin.close();
}

int student::search() {
    int r, i = 0;
    ifstream fin;
    fin.open("stud.dat", ios::in | ios::binary);
    
    if (!fin) {
        cout << "\n\tError opening file!";
        return -1;
    }

    cout << "\nEnter Roll No: ";
    cin >> r;

    while(fin.read((char*)&rec, sizeof(stud))) {
        if(rec.roll == r) {
            cout << "\n\tRecord Found...\n";
            cout << "\n\tRoll\tName\tDiv\tAddress\n";
            cout << "\n\t" << rec.roll << "\t" << rec.name << "\t" << rec.div << "\t" << rec.add;
            return i;  
        }
        i++;
    }

    fin.close();
    return -1; 
}

void student::Delete() {
    int pos = search();
    if (pos == -1) {
        cout << "\n\tRecord Not Found\n";
        return;
    }

    fstream f;
    f.open("stud.dat", ios::in | ios::out | ios::binary);
    if (!f) {
        cout << "\n\tError opening file!";
        return;
    }

    int offset = pos * sizeof(stud);
    f.seekp(offset, ios::beg);

    rec.roll = -1;
    strcpy(rec.name, "NULL");
    rec.div = 'N';
    strcpy(rec.add, "NULL");

    f.write((char*)&rec, sizeof(stud));
    f.close();

    cout << "\n\tRecord Deleted\n";
}

int main() {
    student obj;
    int ch, key;
    char ans;

    do {
        cout << "\n\t***** Student Information *****";
        cout << "\n\t1. Create";
        cout << "\n\t2. Display";
        cout << "\n\t3. Delete";
        cout << "\n\t4. Search";
        cout << "\n\t5. Exit";
        cout << "\n\nEnter Your Choice: ";
        cin >> ch;

        switch(ch) {
            case 1:
                obj.create();
                break;
            case 2:
                obj.display();
                break;
            case 3:
                obj.Delete();
                break;
            case 4:
                key = obj.search();
                if (key == -1) 
                    cout << "\n\tRecord Not Found...\n";
                break;
            case 5:
                cout << "\n\tExiting the program.";
                break;
            default:
                cout << "\n\tInvalid choice, please try again.";
        }

        if (ch != 5) {
            cout << "\n\t..... Do You Want to Continue in Main Menu (y/n): ";
            cin >> ans;
        }

    } while(ans == 'y' || ans == 'Y');

    return 0;
}

