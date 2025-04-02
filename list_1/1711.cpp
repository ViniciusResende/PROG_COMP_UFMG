#include <iostream>
#include <list>

using namespace std;

#define INF 0x3f3f3f3f

struct Edge {
  int weight = 0;
  int src, dest;
};

class Graph {
  private:
    int V;
    int E;
    int edgeId = 0;
    Edge* edges;
  public:
    Graph(int V, int E);
    void addEdge(int v, int u, int weight);
    void BellmanFord(int src);
};

Graph::Graph(int V, int E) {
  this->V = V;
  this->E = E;
  this->edges = new Edge[V];
}

void Graph::addEdge(int v, int u, int weight) {
  this->edges[this->edgeId].src = v;
  this->edges[this->edgeId].dest = u;
  this->edges[this->edgeId].weight = weight;

  this->edgeId++;
}

void printArr(int dist[], int n) {
  printf("Vertex   Distance from Source\n");
  for (int i = 0; i < n; ++i)
    printf("%d \t\t %d\n", i, dist[i]);
}

void Graph::BellmanFord(int src) {
  int dist[this->V];

  // Step 1: Initialize distances from src to all other
  // vertices as INFINITE
  for (int i = 0; i < this->V; i++)
      dist[i] = INF;
  dist[src] = 0;

  // Step 2: Relax all edges |V| - 1 times. A simple
  // shortest path from src to any other vertex can have
  // at-most |V| - 1 edges
  for (int i = 1; i <= V - 1; i++) {
    for (int j = 0; j < E; j++) {
      int u = this->edges[j].src;
      int v = this->edges[j].dest;
      int weight = this->edges[j].weight;
      if (dist[u] != INF
        && dist[u] + weight < dist[v])
        dist[v] = dist[u] + weight;
    }
  }

  printArr(dist, V);

  return;
}

int main() {
  int S = 0, T = 0;
  while(cin >> S >> T) {

    Graph G(S, T);
    for(int i = 0; i < T; i++) {
      int A, B, C;
      cin >> A >> B >> C;
      A--; B--;

      G.addEdge(A, B, C);
    }

    int Q = 0;
    cin >> Q;

    for(int i = 0; i < Q; i++) {
      int X, M;
      cin >> X >> M;
      X--;
      G.BellmanFord(X);
    }
  }
  
  return 0;
}