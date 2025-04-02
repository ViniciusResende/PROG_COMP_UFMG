#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct UnionFindEl {
  int parent, rank;
};

class UnionFind {
  public:
    int size;
    vector<UnionFindEl> nodes;

    UnionFind(int size) {
      this->size = size;
      this->nodes = vector<UnionFindEl>(size);

      for (int i = 0; i < size; i++) {
        this->nodes[i].parent = i;
        this->nodes[i].rank = 0;
      }
    }

    int find(int idx){
      if (this->nodes[idx].parent != idx) {
        this->nodes[idx].parent = this->find(nodes[idx].parent);
      }

      return nodes[idx].parent;
    }

    void unionElements(int a, int b) {
      int representantOfA = this->find(a);
      int representantOfB = this->find(b);

      if (nodes[representantOfA].rank > nodes[representantOfB].rank)
        nodes[representantOfB].parent = representantOfA;
      else if (nodes[representantOfA].rank < nodes[representantOfB].rank)    
        nodes[representantOfA].parent = representantOfB;
      else
        nodes[representantOfB].parent = representantOfA;
        nodes[representantOfA].rank++;
    }
};

struct Edge {
  int src;
  int dest;
  int weight;
};

class Graph {
  private:
    int lastFreeEdge = 0;
  public:
    int N, M;
    Edge *edges;

    Graph(int N, int M) {
      this->N = N;
      this->M = M;

      this->edges = new Edge[N];
    }

    void addEdge(int src, int dest, int weight) {
      edges[lastFreeEdge] = Edge({ src, dest, weight });
      lastFreeEdge++;
    }

    int Kruskal() {
      Edge mst[this->N];
      UnionFind UF = UnionFind(this->N);    

      int prevEdgeIdx = 0, i = 0;
      while((prevEdgeIdx < this->N - 1) && (i < this->M)) {
        Edge currEdge = this->edges[i];
        
        int rootSrc = UF.find(currEdge.src);
        int rootDest = UF.find(currEdge.dest);

        if (rootSrc != rootDest) {
          mst[prevEdgeIdx] = currEdge;
          prevEdgeIdx++;
          UF.unionElements(rootSrc, rootDest);
        }

        i++;
      }

      int totalWeight = 0;
      for (int j = 0; j < prevEdgeIdx; j++) {
        totalWeight += mst[j].weight;
      }

      return totalWeight;
    }
};

int asc(const void *a, const void *b) {
  return ((Edge *)a)->weight > ((Edge *)b)->weight;
}

int desc(const void *a, const void *b) {
  return ((Edge *)a)->weight < ((Edge *)b)->weight;
}

int main(){
  int galleriesCount;
  cin >> galleriesCount;

  Graph *graph = new Graph(galleriesCount, galleriesCount);

  for (int i = 0; i < galleriesCount; i++) {
    int src, dest, weight;
    cin >> src;
    cin >> dest;
    cin >> weight;
    graph->addEdge(src - 1, dest - 1, weight);
  }

  qsort(graph->edges, graph->N, sizeof(graph->edges[0]), asc);
  int minVal = graph->Kruskal();

  qsort(graph->edges, graph->N, sizeof(graph->edges[0]), desc);
  int maxVal = graph->Kruskal();

  cout << maxVal << endl;
  cout << minVal << endl;

  return 0;
}