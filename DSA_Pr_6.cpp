/*There are flight paths between cities. If there is a flight between city A and city B then there is an
edge between the cities. The cost of the edge can be the time that flight takes to reach city B
from A, or the amount of fuel used for the journey. Represent this as a graph. The node can be
represented by airport name or name of the city. Use adjacency list representation of the
graph or use adjacency matrix representation of the graph. Justify the storage
representation used.*/
    
#include <iostream>
#include <queue>
using namespace std;
int adj_mat[50][50] = {0}; // Initialize adjacency matrix to 0
int visited[50] = {0}; // Global visited array for DFS
void dfs(int s, int n, string arr[]) {
    visited[s] = 1;
    cout << arr[s] << " ";
    for (int i = 0; i < n; i++) {
        if (adj_mat[s][i] && !visited[i]) {
            dfs(i, n, arr);
        }
    }
}
void bfs(int s, int n, string arr[]) {
    bool visited[50] = {false}; // Local visited array for BFS
    queue<int> bfsq;
    visited[s] = true;
    cout << arr[s] << " ";
    bfsq.push(s);
    while (!bfsq.empty()) {
        int v = bfsq.front();
        bfsq.pop();
        for (int i = 0; i < n; i++) {
            if (adj_mat[v][i] && !visited[i]) {
                bfsq.push(i);
                visited[i] = true;
                cout << arr[i] << " ";
            }
        }
    }
}
int main() {
    int n, u;
    cout << "Enter the number of cities: ";
    cin >> n;
    string cities[n]; // Array to store city names
    for (int i = 0; i < n; i++) {
        cout << "Enter city " << i + 1 << ": ";
        cin >> cities[i];
    }
    cout << "Enter distances between cities (0 for no connection):\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Distance between " << cities[i] << " and " << cities[j] << ": ";
            cin >> adj_mat[i][j];
            adj_mat[j][i] = adj_mat[i][j]; // Since it's an undirected graph
        }
    }
    // Printing adjacency matrix
    cout << "\nAdjacency Matrix:\n\t";
    for (int i = 0; i < n; i++) {
        cout << cities[i] << "\t";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << cities[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << adj_mat[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "\nEnter starting vertex index (0 to " << n - 1 << "): ";
    cin >> u;
    // DFS Traversal
    cout << "\nDFS Traversal: ";
    fill(begin(visited), end(visited), 0); // Reset visited array
    dfs(u, n, cities);
    cout << "\nBFS Traversal: ";
    bfs(u, n, cities);
    return 0;
}
