#include "graph_en.h"

int main() {
    graph = loadGraphFromCSV(filename);

    // Print the loaded graph data to verify
    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }

    // Find the shortest path from A to H, K, Q, T
    vector<int> dist = dijkstra(0);
    vector<int> path = dijkstra_queue(0);
    
    // Output the shortest path from A to H, K, Q, T
    cout << "Naive Dijkstra algorithm: " << endl;
    cout << "The shortest path length from A to H is: " << dist[7] << endl; // Assuming H is the 7th node
    cout << "The shortest path length from A to K is: " << dist[10] << endl; // Assuming K is the 10th node
    cout << "The shortest path length from A to Q is: " << dist[16] << endl; // Assuming Q is the 16th node
    cout << "The shortest path length from A to T is: " << dist[19] << endl; // Assuming T is the 19th node
    
    // Output the shortest path from A to H, K, Q, T
    cout << "Heap optimized Dijkstra algorithm: " << endl;
    cout << "The shortest path length from A to H is: " << path[7] << endl; // Assuming H is the 7th node
    cout << "The shortest path length from A to K is: " << path[10] << endl; // Assuming K is the 10th node
    cout << "The shortest path length from A to Q is: " << path[16] << endl; // Assuming Q is the 16th node
    cout << "The shortest path length from A to T is: " << path[19] << endl; // Assuming T is the 19th node
    
    return 0;
}
