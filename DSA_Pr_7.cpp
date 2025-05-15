/*Represent given graph using adjacency matrix/list to perform DFS and adjacency list to perform BFS. 
Use map of area around the college as a graph. Identify prominent landmark as nodes and perform DFS and BFS on that.*/
    
#include <iostream>
#include <queue>
#include <map>
#include <list>
#include <stack>
#include <vector>
using namespace std;

// Define a simple structure for the graph with an adjacency matrix for DFS and an adjacency list for BFS
class Graph {
private:
    int V;  // Number of vertices (landmarks)
    map<string, int> landmarkIndex; // Map to store landmark names to indices
    map<int, string> indexLandmark; // Map to store index to landmark names
    vector<vector<int>> adjMatrix; // Adjacency matrix for DFS (dynamic size)
    vector<list<int>> adjList;   // Adjacency list for BFS (dynamic size)

public:
    Graph() {
        this->V = 0; // Initially, no landmarks
    }

    // Method to add landmark and map it to an index
    void addLandmark(string landmark) {
        landmarkIndex[landmark] = V;
        indexLandmark[V] = landmark;
        V++;

        // Resize the adjacency matrix and list to accommodate the new landmark
        adjMatrix.resize(V, vector<int>(V, 0));
        adjList.resize(V);
    }

    // Method to add an edge between two landmarks
    void addEdge(string landmark1, string landmark2) {
        int u = landmarkIndex[landmark1];
        int v = landmarkIndex[landmark2];
        
        // For DFS - Adjacency matrix representation
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // Assuming undirected graph
        
        // For BFS - Adjacency list representation
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Assuming undirected graph
    }

    // Depth First Search (DFS) using adjacency matrix
    void DFS(int start, bool visited[]) {
        stack<int> s;
        s.push(start);
        visited[start] = true;
        
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            cout << "Visited " << indexLandmark[current] << endl;  // Print the actual landmark name
            
            for (int i = 0; i < V; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    s.push(i);
                    visited[i] = true;
                }
            }
        }
    }

    // Breadth First Search (BFS) using adjacency list
    void BFS(int start) {
        bool visited[V] = {false}; // Array of visited landmarks
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << "Visited " << indexLandmark[current] << endl;  // Print the actual landmark name

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
};

int main() {
    // Create a graph object
    Graph g;

    // Add landmarks to the graph
    g.addLandmark("Canteen");
    g.addLandmark("Ground");
    g.addLandmark("Labs");
    g.addLandmark("Library");
    g.addLandmark("Parking");

    // Add edges (connections between landmarks)
    g.addEdge("Canteen", "Ground");
    g.addEdge("Ground", "Labs");
    g.addEdge("Labs", "Library");
    g.addEdge("Library", "Parking");
    g.addEdge("Parking", "Canteen");

    // Perform DFS starting from "Canteen" (represented by index 0)
    cout << "Depth First Search (DFS):" << endl;
    bool visited[5] = {false};  // Array to track visited landmarks
    g.DFS(0, visited); // DFS from "Canteen"

    // Perform BFS starting from "Canteen" (represented by index 0)
    cout << "\nBreadth First Search (BFS):" << endl;
    g.BFS(0); // BFS from "Canteen"

    return 0;
}

