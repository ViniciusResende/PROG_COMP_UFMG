#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
 
using namespace std;
#define INF 0x3f3f3f3f
typedef pair<int, int> iPair;

struct Edge {
  int weight = 0;
  int dest;
};

class Graph {
  private:
    int V;
    int M;
    list<Edge>* adj;
  public:
    Graph(int V, int M);
    void addEdge(int v, int u, int weightV, int weightU);
    int* dijkstra(int source, int dist[]);
};

Graph::Graph(int V, int M) {
  this->V = V;
  this->M = M;

  this->adj = new list<Edge>[V];
}

void Graph::addEdge(int v, int u, int weightV, int weightU) {
  Edge edge1, edge2;

  edge1.dest = u; edge1.weight = weightU;
  edge2.dest = v; edge2.weight = weightV;

  this->adj[v].push_back(edge1);
  this->adj[u].push_back(edge2);
}

int* Graph::dijkstra(int source, int dist[]) { 
  priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

  for(int i = 0; i < this->V; i++) {
    if(i != source) dist[i] = INF;

    pq.push(make_pair(dist[i], i));
  }

  while(!pq.empty()) {
    int u = pq.top().second;
    pq.pop();

    for(list<Edge>::iterator it = this->adj[u].begin(); it != this->adj[u].end(); it++) {
      int path = dist[u] + it->weight;
      if(path < dist[it->dest]) {
        dist[it->dest] = path;
        pq.push(make_pair(dist[it->dest], it->dest));
      }
    }
  }

  return dist;
}

int main() {
  int N = 0, M = 0, K = 0;
  double killChance = 0.0;

  while(cin >> N) {
    cin >> M;
    cin >> K;
    cin >> killChance;

    Graph G(N, M);

    vector<iPair> edgesToAdd(M);
    for(int i = 0; i < M; i++) {
      int v, u;
      cin >> v;
      cin >> u;
      v--; u--;

      edgesToAdd[i] = make_pair(v, u);
    }

    int A = 0;

    cin >> A;
    vector<int> soldiers(N, 0);
    for(int i = 0; i < A; i++) {
      int soldierPosition;
      cin >> soldierPosition;
      soldiers[soldierPosition - 1]++;
    }

    for(int i = 0; i < M; i++) {
      iPair edge = edgesToAdd[i];
      int v = edge.first;
      int u = edge.second;
      G.addEdge(v, u, soldiers[v], soldiers[u]);
    }

    int origin, dest;
    cin >> origin;
    cin >> dest;
    origin--; dest--;

    int* dist = (int*)malloc(sizeof(int) * N);
    dist[origin] = soldiers[origin];
    dist = G.dijkstra(origin, dist);

    int soldiersEncountered = dist[dest];

    if(soldiersEncountered > K) {
      cout << fixed << setprecision(3) << 0.000 << endl;
      continue;
    }

    double probability = round(pow(killChance, soldiersEncountered) * 1000) / 1000;
    cout << fixed << setprecision(3) << probability << endl;
  }

  return 0;
}