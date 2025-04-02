#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int capacity;
};

int minHopsToPassFlow(int n, int flux, vector<vector<Edge>>& graph) {
    // State to track minimum hops needed to send a certain amount of flow to each vertex
    vector<vector<int>> minHops(n + 1, vector<int>(flux + 1, INT_MAX));
    
    // Queue for BFS: (current vertex, current flow sent, current hops)
    queue<tuple<int, int, int>> q;

    // Initialize the queue with the starting vertex 1
    q.push({1, 0, 0}); // (vertex 1, flow 0, hops 0)
    minHops[1][0] = 0;

    while (!q.empty()) {
        int current, currentFlow, currentHops;
        tie(current, currentFlow, currentHops) = q.front();
        q.pop();

        for (const Edge& edge : graph[current]) {
            int next = edge.to;
            int capacity = edge.capacity;

            // For each possible additional flow to be sent through this edge
            for (int sent = 1; sent <= capacity; ++sent) {
                int newFlow = currentFlow + sent;
                if (newFlow > flux) continue;

                if (minHops[next][newFlow] > currentHops + 1) {
                    minHops[next][newFlow] = currentHops + 1;
                    q.push({next, newFlow, currentHops + 1});
                }
            }
        }
    }

    // Find the minimum hops to send exactly 'flux' amount of flow to vertex n
    int result = minHops[n][flux];
    return (result == INT_MAX) ? -1 : result;
}

int main() {
    int n = 3; // Number of vertices
    int flux = 5; // The required flux to pass
    vector<vector<Edge>> graph(n + 1);

    // Example graph edges with capacities
    graph[1].push_back({2, 1});
    graph[1].push_back({3, 1});
    graph[2].push_back({3, 5});
    graph[3].push_back({1, 4});

    int result = minHopsToPassFlow(n, flux, graph);
    if (result != -1) {
        cout << "Minimum number of hops to pass the flow from 1 to " << n << " is: " << result << endl;
    } else {
        cout << "No path exists from 1 to " << n << endl;
    }

    return 0;
}
