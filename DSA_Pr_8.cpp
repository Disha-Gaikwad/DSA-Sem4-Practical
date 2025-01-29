#include <iostream>
#include <list>
#include <iterator>
#include <string>

using namespace std;

class Dictionary 
{
private:
    static const int TABLE_SIZE = 10;  
    list<pair<string, string>>* table;  

    int hashFunction(string key) 
	{
        int hash = 0;
        for (int i = 0; i < key.length(); i++) 
		{
            hash = (hash + key[i]) % TABLE_SIZE;  
        }
        return hash;
    }

public:
    Dictionary() 
	{
        table = new list<pair<string, string>>[TABLE_SIZE];
    }
    ~Dictionary() 
	{
        delete[] table;
    }

    void insert(string key, string value) 
	{
        int index = hashFunction(key);  
        for (auto& entry : table[index]) 
		{
            if (entry.first == key) 
			{
                entry.second = value;  // Update value if key exists
                cout << "Key " << key << " updated with new value: " << value << endl;
                return;
            }
        }
        
        table[index].push_back(make_pair(key, value));
        cout << "Inserted (" << key << ", " << value << ") into dictionary." << endl;
    }

    string find(string key) 
	{
        int index = hashFunction(key);  // Find the index using the hash function
        for (auto& entry : table[index]) 
		{
            if (entry.first == key) 
			{
                return entry.second;  // Return the value associated with the key
            }
        }
        return "Key not found";  // Return message if key is not found
    }

    void deleteKey(string key) 
	{
        int index = hashFunction(key);  // Find the index using the hash function
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) 
		{
            if (it->first == key) 
			{
                bucket.erase(it);  // Remove the key-value pair
                cout << "Key " << key << " deleted from dictionary." << endl;
                return;
            }
        }
        cout << "\nKey " << key << " not found for deletion." << endl;  // If key is not found
    }

    void display() 
	{
        for (int i = 0; i < TABLE_SIZE; i++) 
		{
            if (!table[i].empty()) 
			{
                cout << "Bucket " << i << ": ";
                for (auto& entry : table[i]) 
				{
                    cout << "(" << entry.first << ", " << entry.second << ") ";
                }
                cout << endl;
            }
        }
    }
};

int main() 
{
    Dictionary dict;

    dict.insert("apple", "fruit");
    dict.insert("carrot", "vegetable");
    dict.insert("dog", "animal");
    dict.insert("banana", "fruit");

    //Display the dictionary
    cout << "\nDisplaying dictionary:" << endl;
    dict.display();

    // Find a value by key
    string key = "carrot";
    cout << "\nFind 'carrot': " << dict.find(key) << endl;

    // Delete a key-value pair
    dict.deleteKey("dog");

    // Display the dictionary after deletion
    cout << "\nDisplaying dictionary after deletion:" << endl;
    dict.display();

    // Try to find a deleted key
    key = "dog";
    cout << "\nFind 'dog': " << dict.find(key) << endl;

    return 0;
}

