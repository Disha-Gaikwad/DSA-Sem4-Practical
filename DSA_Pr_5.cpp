/*Consider Telephone book database of N clients. Make use of hash table implementation to
quickly look up clients telephone number.*/

#include<iostream>
#include <string>
using namespace std;

class Telephone
{
    int hash_address;
    long int key;
    int x;
    int mobno[10];
    string name[10];

public:
    Telephone()
    {
     
        for(int i = 0; i < 10; i++)
        {
            mobno[i] = -1;
        }
    }

    
    void insertRecord_LP()
    {
        cout << "Enter number of records: ";
        cin >> x;

        for(int i = 0; i < x; i++)
        {
            cout << "Enter telephone number: ";
            cin >> key;

            hash_address = key % 10;

            if (mobno[hash_address] == -1)
            {
                mobno[hash_address] = key;
                cout << "Enter name: ";
                cin >> name[hash_address];
            }
            else
            {
               
                int j = 1;
                while (mobno[(hash_address + j) % 10] != -1)
                {
                    j++;
                }
                hash_address = (hash_address + j) % 10;
                mobno[hash_address] = key;
                cout << "Enter name: ";
                cin >> name[hash_address];
            }
        }
    }


    void insertRecord_QP()
    {
        cout << "Enter number of records: ";
        cin >> x;

        for(int i = 0; i < x; i++)
        {
            cout << "Enter telephone number: ";
            cin >> key;

            hash_address = key % 10;

            if (mobno[hash_address] == -1)
            {
                mobno[hash_address] = key;
                cout << "Enter name: ";
                cin >> name[hash_address];
            }
            else
            {
               
                int j = 1;
                while (mobno[(hash_address + j * j) % 10] != -1)
                {
                    j++;
                }
                hash_address = (hash_address + j * j) % 10;
                mobno[hash_address] = key;
                cout << "Enter name: ";
                cin >> name[hash_address];
            }
        }
    }

    
    void display()
    {
        for(int i = 0; i < 10; i++)
        {
            if (mobno[i] != -1) 
                cout << i << " " << mobno[i] << "->" << name[i] << endl;
        }
    }
};

int main()
{
    Telephone t1;
    int ch;

    do
    {
        cout << "\n1. Insert Record (Linear Probing)" << endl;
        cout << "2. Insert Record (Quadratic Probing)" << endl;
        cout << "3. Display Records" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        switch(ch)
        {
            case 1:
                t1.insertRecord_LP();
                break;
            case 2:
                t1.insertRecord_QP();
                break;
            case 3:
                t1.display();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (ch != 4);

    return 0;
}


