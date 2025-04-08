#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
    int empID;
    string name;
    string designation;
    float salary;
};

void addEmployee() {
    Employee emp;
    ofstream file("employees.txt", ios::app);

    cout << "Enter Employee ID: ";
    cin >> emp.empID;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, emp.name);
    cout << "Enter Designation: ";
    getline(cin, emp.designation);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    file << emp.empID << " " << emp.name << " " << emp.designation << " " << emp.salary << endl;
    file.close();

    cout << "Employee added successfully!\n";
}

void displayEmployee(int searchID) {
    ifstream file("employees.txt");
    Employee emp;
    bool found = false;

    while (file >> emp.empID >> emp.name >> emp.designation >> emp.salary) {
        if (emp.empID == searchID) {
            cout << "\nEmployee Found:\n";
            cout << "ID: " << emp.empID << "\nName: " << emp.name
                 << "\nDesignation: " << emp.designation
                 << "\nSalary: " << emp.salary << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Employee with ID " << searchID << " not found.\n";
}

void deleteEmployee(int deleteID) {
    ifstream inFile("employees.txt");
    ofstream outFile("temp.txt");
    Employee emp;
    bool found = false;

    while (inFile >> emp.empID >> emp.name >> emp.designation >> emp.salary) {
        if (emp.empID == deleteID) {
            found = true;
        } else {
            outFile << emp.empID << " " << emp.name << " " << emp.designation << " " << emp.salary << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove("employees.txt");
    rename("temp.txt", "employees.txt");

    if (found)
        cout << "Employee deleted successfully.\n";
    else
        cout << "Employee with ID " << deleteID << " not found.\n";
}

int main() {
    int choice, id;

    do {
        cout << "\n--- Employee Management ---\n";
        cout << "1. Add Employee\n2. Display Employee\n3. Delete Employee\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                cout << "Enter Employee ID to display: ";
                cin >> id;
                displayEmployee(id);
                break;
            case 3:
                cout << "Enter Employee ID to delete: ";
                cin >> id;
                deleteEmployee(id);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
