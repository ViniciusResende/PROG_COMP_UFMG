#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

class Edge {
public:
  int src, dest, cap, flow = 0;
  Edge(int src, int dest, int cap) {
    this->src = src;
    this->dest = dest;
    this->cap = cap;
  }
};

class Graph {
private:
  vector<Edge> edges;
  vector<vector<int>> adjacency_list;
  int src, target;
  int lastAdded = 0;
  vector<int> breadth;

  int getHandledFlow(int src, int availableFlow) {
    if (availableFlow == 0) return 0;
    if (src == this->target) return availableFlow;

    for (const int edge : this->adjacency_list[src]) {
      int dest = this->edges[edge].dest;
      bool canGoNext = this->breadth[src] + 1 == this->breadth[dest];
      bool canHandleFlow = (this->edges[edge].cap - this->edges[edge].flow) > 0;
      if (canGoNext && canHandleFlow) {
        int currentHandledFlow = this->getHandledFlow(dest, min(availableFlow, this->edges[edge].cap - this->edges[edge].flow));
        if (currentHandledFlow != 0) {
          this->edges[edge ^ 1].flow -= currentHandledFlow; // mirrored edge
          this->edges[edge].flow += currentHandledFlow;

          return currentHandledFlow;
        }
      }
    }
    
    return 0;
  }

  bool targetIsReachable()  {
    queue<int> q;
    fill(this->breadth.begin(), this->breadth.end(), -1);
    this->breadth[this->src] = 0;
    q.push(this->src);
    while (!q.empty()) {
      int v = q.front();
      q.pop();

      for (const int edge : this->adjacency_list[v]) {
        bool visited = this->breadth[this->edges[edge].dest] != -1;
        bool canHandleFlow = (this->edges[edge].cap - this->edges[edge].flow) > 0;
        if (!visited && canHandleFlow) {
          q.push(this->edges[edge].dest);
          this->breadth[this->edges[edge].dest] = this->breadth[v] + 1;
        }
      }
    }

    return breadth[this->target] != -1;
  }

public:
  Graph(int size, int src, int target) {
    this->src = src;
    this->target = target;
    adjacency_list.resize(size);
    breadth.resize(size);
  }

  void addEdge(int src, int dest, int cap) {
    this->adjacency_list[src].push_back(lastAdded);
    this->adjacency_list[dest].push_back(lastAdded + 1);
    this->edges.push_back(Edge(src, dest, cap));
    this->edges.push_back(Edge(dest, src, 0));
    lastAdded += 2;
  }

  int graphMaxFlow() {
    int accumulator = 0;

    while (this->targetIsReachable()) {
      while (int flow = this->getHandledFlow(this->src, INF)) accumulator += flow;
    }

    return accumulator;
  }
};

int main() {
  map<string, int> shirtIds;
  shirtIds["XS"] = 0;
  shirtIds["S"] = 1;
  shirtIds["M"] = 2;
  shirtIds["L"] = 3;
  shirtIds["XL"] = 4;
  shirtIds["XXL"] = 5;

  int testCases;
  cin >> testCases;
  while(testCases--) {
    int shirts, voluntaries, diffShirtsAmount = 6;
    cin >> shirts >> voluntaries;

    int vertices = voluntaries + diffShirtsAmount + 2;
    int src = voluntaries + diffShirtsAmount, tgt = voluntaries + diffShirtsAmount + 1;
    Graph graph(vertices, src, tgt);

    // src reaches voluntaries
    for (int i = 0; i < voluntaries; i++) {
      graph.addEdge(src, i, 1);
    }

    // shirt sizes reaches terminal
    for (int i = 0; i < 6; i++) {
      graph.addEdge(voluntaries + i, tgt, shirts / 6);
    }

    string shirt1, shirt2;
    // Voluntaries reaches shirts
    for (int i = 0; i < voluntaries; i++) {
      cin >> shirt1 >> shirt2;
      graph.addEdge(i, shirtIds[shirt1] + voluntaries, 1);
      graph.addEdge(i, shirtIds[shirt2] + voluntaries, 1);
    }

    int maxFlow = graph.graphMaxFlow();
    cout << ((maxFlow >= voluntaries) ? "YES" : "NO") << endl;
  }

  return 0;
}