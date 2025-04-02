#include <algorithm>
#include <iostream>
#include <queue>
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

  int getHandledFlow(int src, int availableFlow) {
    if (availableFlow == 0) return 0;
    if (src == this->target) return availableFlow;

    for (const int edge : this->adjacency_list[src]) {
      int dest = this->edges[edge].dest;
      bool canGoNext = this->breadth[src] + 1 == this->breadth[dest];
      bool canHandleFlow = (this->edges[edge].cap - this->edges[edge].flow) > 0;
      if (canGoNext && canHandleFlow) {
        int currentHandledFlow = getHandledFlow(dest, min(availableFlow, this->edges[edge].cap - this->edges[edge].flow));
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

  int graphMaxFlow() {
    int accumulator = 0;

    while (targetIsReachable()) {
      while (int flow = getHandledFlow(this->src, INF)) accumulator += flow;
    }

    return accumulator;
  }
};

int main() {
  int types, categories;
  while (cin >> types) {
    cin >> categories;

    int vertices = types + categories;
    Graph G(vertices + 2, vertices + 1, 0);

    for (int i = 1; i <= types; i++) {
      int cost;
      cin >> cost;
      G.addEdge(i, 0, cost);
    }

    vector<int> vodkasPerCategory(categories);
    for (int i = 0; i < categories; i++) {
      cin >> vodkasPerCategory[i];
    }

    int maxBenefit = 0;
    for (int i = 0; i < categories; i++) {
      int B;
      cin >> B;
      maxBenefit += B;
      G.addEdge(vertices + 1, i + types + 1, B);
      for (int j = 0; j < vodkasPerCategory[i]; j++) {
        int curr;
        cin >> curr;
        G.addEdge(i + types + 1, curr, INF);
      }
    }

    int maxValue = maxBenefit - G.graphMaxFlow();
    cout << abs(maxValue) << endl;
  }

  return 0;
}