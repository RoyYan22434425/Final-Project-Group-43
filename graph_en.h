#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>
#include <limits>
#include <chrono>

using namespace std;
string filename = "graph.csv"; // Assume the CSV file name is graph.csv
// Define the size of the graph
const int V = 23; // Declare a global variable for the number of nodes, A to W, 23 nodes in total
const int INF = INT_MAX; // Define a value representing infinity
vector<vector<int>> graph; // 2D array graph

// Function: Load the graph from a CSV file and return a 2D array
vector<vector<int>> loadGraphFromCSV(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> graph;
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        vector<int> row;
        string value;
        while (getline(ss, value, ',')) {
            // Check if the string is empty or only contains spaces
            if (!value.empty() && value.find_first_not_of(' ') != string::npos) {
                try {
                    row.push_back(stoi(value));
                } catch (const invalid_argument& e) {
                    cerr << "Unconvertible value: " << value << endl;
                    // Or set a default value, for example, 0
                    // row.push_back(0);
                }
            }
        }
        graph.push_back(row);
    }
    return graph;
}

// Function: Reconstruct and print the shortest path
void printShortestPath(vector<int>& predecessors, int src, int dest) {
    if (dest == src) {
        cout << src << " ";
        return;
    }
    printShortestPath(predecessors, src, predecessors[dest]);
    cout << dest << " ";
}

// Implement Dijkstra's algorithm
vector<int> dijkstra(int src) {
    vector<int> dist(V, INF); // Initialize the distance array
    vector<bool> visited(V, false); // Initialize the status array
    dist[src] = 0; // The distance from the source node to itself is 0

    // Get the start time point
    auto start_1 = chrono::high_resolution_clock::now();

    for (int i = 0; i < V - 1; i++) {
        int u = -1; // Find the node with the minimum distance among the unvisited nodes
        for (int j = 0; j < V; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = true; // Mark node u as visited

        // Update the distance of the neighbors of node u
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && !visited[v]) {
                dist[v] = min(dist[v], dist[u] + graph[u][v]);
            }
        }
    }

    // Get the end time point
    auto end_1 = chrono::high_resolution_clock::now();
    // Calculate and print the function running time
    chrono::duration<double> elapsed_1 = end_1 - start_1;
    cout << "Naive Dijkstra algorithm function running time: " << elapsed_1.count() << " seconds" << endl;

    return dist; // Return the distance array
}

// Heap-optimized Dijkstra's algorithm
vector<int> dijkstra_queue(int src) {
    vector<int> dist(V, INF);
    vector<bool> visited(V, false);
    vector<int> predecessors(V, -1);
    dist[src] = 0;

    // Use a priority queue, sorted by distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    // Get the start time point
    auto start_2 = chrono::high_resolution_clock::now();
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && !visited[v]) {
                int alt = dist[u] + graph[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    pq.push({alt, v});
                    predecessors[v] = u;
                }
            }
        }
    }

    // Get the end time point
    auto end_2 = chrono::high_resolution_clock::now();
    // Calculate and print the function running time
    chrono::duration<double> elapsed_2 = end_2 - start_2;
    cout << "Heap-optimized Dijkstra algorithm function running time: " << elapsed_2.count() << " seconds" << endl;

    // Example: Print the shortest path from the source node to specific destination nodes
    cout << "The shortest path from A to H is: ";
    printShortestPath(predecessors, 0, 7);
    cout<<endl << "The shortest path from A to K is: ";
    printShortestPath(predecessors, 0, 10);
    cout<<endl << "The shortest path from A to Q is: ";
    printShortestPath(predecessors, 0, 16);
    cout<<endl << "The shortest path from A to T is: ";
    printShortestPath(predecessors, 0, 19);
    cout << endl;

    return dist;
}
