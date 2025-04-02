#include <iostream>
#include <vector>
#include <queue>
 
using namespace std;
#define INF 0x3f3f3f3f
typedef pair<int, int> iPair;


int* dijkstra(int** graph, int source, int n, int dist[]) {
  dist[source] = 0;

  std::priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

  for(int i = 0; i < n; i++) {
    if(i != source)
      dist[i] = INF;

    pq.push(make_pair(dist[i], i));
  }

  while(!pq.empty()) {
    int u = pq.top().second;
    pq.pop();

    for(int v = 0; v < n; v++) {
      int path = dist[u] + graph[u][v];
      if(path < dist[v]) {
        dist[v] = path;
        pq.push(make_pair(dist[v], v));
      }
    }
  }

  return dist;
}

int main() {
  int n, m, server;
  
  cin >> n;
  cin >> m;

  int** graph = (int**) malloc(n * sizeof(int*));
  for(int i = 0; i < n; i++) {
    graph[i] = (int*)malloc(n * sizeof(int));
    for(int j = 0; j < n; j++) {
      graph[i][j] = INF;
    }
  }

  for(int i = 0; i < m; i++) {
    int u, v, w;

    cin >> u;
    cin >> v;
    cin >> w;

    u -= 1; // translates to index
    v -= 1; // translates to index

    graph[u][v] = w;
    graph[v][u] = w;
  }

  cin >> server;
  server -= 1; // translates to index

  int dist[n]; 
  dijkstra(graph, server, n, dist);

  int closestIslandDistance = INF;
  int furthestIslandDistance = -INF;

  for(int i = 0; i < n; i++) {
    if(i != server) {
      if(dist[i] > furthestIslandDistance) furthestIslandDistance = dist[i];
      if(dist[i] < closestIslandDistance) closestIslandDistance = dist[i];
    }
  }

  std::cout << furthestIslandDistance - closestIslandDistance << std::endl;

  return 0;
}