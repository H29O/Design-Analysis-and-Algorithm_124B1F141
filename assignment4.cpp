#include <bits/stdc++.h>
using namespace std;

// Dijkstra's Algorithm
void dijkstra(int source,
              vector<vector<pair<int, int>>> &graph,
              vector<int> &dist) {

    int V = graph.size();

    // Initially, distance to every vertex is infinity
    dist.assign(V, INT_MAX);

    // Distance from source to itself is 0
    dist[source] = 0;

    // Min-heap: {distance, vertex}
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    pq.push({0, source});

    while (!pq.empty()) {

        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        // Ignore outdated distance
        if (d > dist[u])
            continue;

        // Check all neighbours of u
        for (auto edge : graph[u]) {

            int v = edge.first;
            int w = edge.second;

            // Relaxation
            if (dist[v] > dist[u] + w) {

                dist[v] = dist[u] + w;

                pq.push({dist[v], v});
            }
        }
    }
}

int main() {

    int V, E;

    cout << "Enter number of intersections (vertices): ";
    cin >> V;

    cout << "Enter number of roads (edges): ";
    cin >> E;

    // Create graph with V vertices
    vector<vector<pair<int, int>>> graph(V);

    cout << "Enter edges (u v w):\n";

    for (int i = 0; i < E; i++) {

        int u, v, w;
        cin >> u >> v >> w;

        // Undirected road
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    // Ambulance starting point
    int source;

    cout << "Enter ambulance start location (source): ";
    cin >> source;

    // Number of hospitals
    int H;

    cout << "Enter number of hospitals: ";
    cin >> H;

    // Store hospital nodes
    vector<int> hospitals(H);

    cout << "Enter hospital nodes: ";

    for (int i = 0; i < H; i++) {
        cin >> hospitals[i];
    }

    // Run Dijkstra from ambulance location
    vector<int> dist;

    dijkstra(source, graph, dist);

    // Find nearest hospital
    int minTime = INT_MAX;
    int nearestHospital = -1;

    for (int h : hospitals) {

        if (dist[h] < minTime) {

            minTime = dist[h];
            nearestHospital = h;
        }
    }

    // Display result
    if (nearestHospital == -1 || minTime == INT_MAX) {

        cout << "No hospital reachable.\n";
    }
    else {

        cout << "Nearest hospital is at node "
             << nearestHospital
             << " with travel time "
             << minTime
             << " minutes.\n";
    }

    return 0;
}
