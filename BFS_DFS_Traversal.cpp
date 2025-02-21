#include <iostream> 
#include <queue>
#include <stack>
using namespace std;

void printGraph(int arr[6][6], int n) { 
    cout << "Adjacency Matrix:" << endl; 
    for (int i = 0; i < n; i++) { 
        cout << "\t"; 
        for (int j = 0; j < n; j++) { 
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void bfs(int arr[6][6], int n, int start) { 
    cout << "BFS Traversal of Graph:" << endl; 
    bool visited[n] = {false};
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop(); 
        cout << node + 1 << " ";
        for (int i = 0; i < n; i++) { 
            if (arr[node][i] == 1 && !visited[i]) { 
                q.push(i); 
                visited[i] = true; // Corrected this line
            }
        }
    } 
    cout << endl;
}

void dfs(int gr[6][6], int n, int start) { 
    cout << "DFS Traversal of Graph:" << endl; 
    bool visited[n] = {false};
    stack<int> s; 
    s.push(start);

    while (!s.empty()) {
        int node = s.top(); 
        s.pop();
        if (!visited[node]) {
            cout << node + 1 << " ";
            visited[node] = true;
        }
        for (int i = 0; i < n; i++) {
            if (gr[node][i] == 1 && !visited[i]) {
                s.push(i);
            }
        }
    }
    cout << endl;
}

int main() {
    int gr[6][6] = {
        {0, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 1},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 0, 0}
    };

    int ch;
    do {
        cout << "\n==========================================" << endl;
        cout << "1. Display Graph" << endl;
        cout << "2. BFS Traversal" << endl;
        cout << "3. DFS Traversal" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        cout << "===========================================" << endl;

        switch (ch) {
            case 1:
                printGraph(gr, 6); // Correct the size to 6
                break;
            case 2: {
                int startNode;
                cout << "Enter the starting node for BFS traversal: ";
                cin >> startNode;
                bfs(gr, 6, startNode - 1);
                break;
            }
            case 3: {
                int startNode;
                cout << "Enter the starting node for DFS traversal: ";
                cin >> startNode; // Fixed the missing semicolon
                dfs(gr, 6, startNode - 1);
                break;
            }
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }
    } while (ch != 4);
    
    cout << "Thank You" << endl;
    return 0;
}

