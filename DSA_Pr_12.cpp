#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

// Function to create or update the index file
void updateIndex() {
    ifstream empFile("employee.dat", ios::binary);
    ofstream idxFile("index.dat", ios::binary);
    
    Employee emp;
    int pos = 0;
    while (empFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        if (emp.id != -1) { // -1 means deleted
            idxFile.write(reinterpret_cast<char*>(&emp.id), sizeof(int));
            idxFile.write(reinterpret_cast<char*>(&pos), sizeof(int));
        }
        pos++;
    }
    empFile.close();
    idxFile.close();
}

// Function to add an employee
void addEmployee() {
    ofstream outFile("employee.dat", ios::binary | ios::app);
    Employee emp;

    cout << "Enter Employee ID: ";
    cin >> emp.id;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(emp.name, 50);
    cout << "Enter Designation: ";
    cin.getline(emp.designation, 50);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    outFile.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
    outFile.close();

    updateIndex();
    cout << "Employee added successfully.\n";
}

// Function to search and display an employee
void displayEmployee() {
    ifstream idxFile("index.dat", ios::binary);
    map<int, int> index;
    int id, pos;

    while (idxFile.read(reinterpret_cast<char*>(&id), sizeof(int))) {
        idxFile.read(reinterpret_cast<char*>(&pos), sizeof(int));
        index[id] = pos;
    }
    idxFile.close();

    int searchId;
    cout << "Enter Employee ID to search: ";
    cin >> searchId;

    if (index.find(searchId) == index.end()) {
        cout << "Employee not found.\n";
        return;
    }

    ifstream empFile("employee.dat", ios::binary);
    empFile.seekg(index[searchId] * sizeof(Employee), ios::beg);
    Employee emp;
    empFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
    empFile.close();

    cout << "\n--- Employee Details ---\n";
    cout << "ID: " << emp.id << "\n";
    cout << "Name: " << emp.name << "\n";
    cout << "Designation: " << emp.designation << "\n";
    cout << "Salary: " << emp.salary << "\n";
}

// Function to delete an employee (mark as deleted)
void deleteEmployee() {
    fstream empFile("employee.dat", ios::in | ios::out | ios::binary);
    ifstream idxFile("index.dat", ios::binary);
    map<int, int> index;
    int id, pos;

    while (idxFile.read(reinterpret_cast<char*>(&id), sizeof(int))) {
        idxFile.read(reinterpret_cast<char*>(&pos), sizeof(int));
        index[id] = pos;
    }
    idxFile.close();

    int deleteId;
    cout << "Enter Employee ID to delete: ";
    cin >> deleteId;

    if (index.find(deleteId) == index.end()) {
        cout << "Employee not found.\n";
        return;
    }

    Employee emp;
    empFile.seekp(index[deleteId] * sizeof(Employee), ios::beg);
    emp.id = -1; // Mark as deleted
    empFile.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
    empFile.close();

    updateIndex();
    cout << "Employee deleted successfully.\n";
}

// Main menu
int main() {
    int choice;
    do {
        cout << "\n===== Employee Management System =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployee(); break;
            case 3: deleteEmployee(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

