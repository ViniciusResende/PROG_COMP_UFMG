#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

struct Edge {
  int src;
  int dest;
  int weight;
};

class Graph {
  public:
    int N, M;
    Edge *edges;

    Graph(int N, int M) {
      this->N = N;
      this->M = M;

      this->edges = new Edge[N];
    }

    // void addEdge(int src, int dest, int weight) {
    //   edges.push_back({ src, dest, weight });
    // }
};

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

      return this->nodes[idx].parent;
    }

    void unionElements(int a, int b) {
      int representantOfA = this->find(a);
      int representantOfB = this->find(b);

      if (this->nodes[representantOfA].rank > this->nodes[representantOfB].rank)
        this->nodes[representantOfB].parent = representantOfA;
      else if (this->nodes[representantOfA].rank < this->nodes[representantOfB].rank)    
        this->nodes[representantOfA].parent = representantOfB;
      else {
        this->nodes[representantOfB].parent = representantOfA;
        this->nodes[representantOfA].rank++;
      }
    }
};

int Kruskal(Graph *graph)
{
    Edge mst[graph->N];
    UnionFind UF = UnionFind(graph->N);

    // for (int v = 0; v < graph->nVert; v++)
    // {
    //     nodes[v].parent = v;
    //     nodes[v].height = 0;
    // }

    int currEdge = 0, i = 0;
    while (currEdge < graph->N - 1 && i < graph->M)
    {
        cout << "test 0" << endl;
        Edge next_edge = graph->edges[i];
        i++;
        int rootX = UF.find(next_edge.src);
        int rootY = UF.find(next_edge.dest);
        cout << "test 1" << endl;
        if (rootX != rootY)
        {
            mst[currEdge] = next_edge;
            currEdge++;
            UF.unionElements(rootX, rootY);
        }
        cout << "test 2" << endl;
    }

    int totalWeight = 0;
    for (int j = 0; j < currEdge; j++)
    {
        totalWeight += mst[j].weight;
    }

    return totalWeight;
}

int Ascending(const void *a, const void *b)
{
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->weight > e2->weight;
}

int Descending(const void *a, const void *b)
{
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->weight < e2->weight;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int nGaleries;
    cin >> nGaleries;

    Graph *graph = new Graph(nGaleries, nGaleries);

    for (int i = 0; i < nGaleries; i++)
    {
        int in, out, w;
        cin >> in >> out >> w;
        graph->edges[i].src = in - 1;
        graph->edges[i].dest = out - 1;
        graph->edges[i].weight = w;
    }

    qsort(graph->edges, graph->N, sizeof(graph->edges[0]), Descending);
    int max = Kruskal(graph);
    qsort(graph->edges, graph->N, sizeof(graph->edges[0]), Ascending);
    int min = Kruskal(graph);

    cout << max << "\n"
         << min << "\n";

    return 0;
}