#include <iostream>
#include <set>
 
using namespace std;

#define MAX_GRAPH_SIZE 26

int letterToIndex(char c) {
  return c - 'a';
}

char indexToLetter(int i) {
  return i + 'a';
}

void DFSRecursive(int** graph, int v, bool visited[], int V, set<char> *reachable) {
  visited[v] = true;
  reachable->insert(indexToLetter(v));

  for(int i = 0; i < V; i++) {
    if(graph[v][i] && !visited[i]) {
      DFSRecursive(graph, i, visited, V, reachable);
    }
  }
}

int connectedComponents(int** graph, int V) {
  int v, amount = 0;
  bool* visited = new bool[V];
  for(v = 0; v < V; v++) visited[v] = false;

  for(v = 0; v < V; v++) {
    if(visited[v] == false) {
      set<char> *reachable = new set<char>();
      DFSRecursive(graph, v, visited, V, reachable);

      amount++;
      set<char>::iterator it;
      for(it = reachable->begin(); it != reachable->end(); it++)
        cout << *it << ",";
      cout << endl;
      delete reachable;
    }
  }

  delete[] visited;
  return amount;
}

void cleanGraph(int** graph, int size) {
  for(int i = 0 ; i < size; i++) {
    for(int j = 0; j < size; j++) {
      graph[i][j] = 0;
    }
  }
}

int main() {
  int testCases;
  cin >> testCases;

  int** graph = (int**) malloc(sizeof(int*) * MAX_GRAPH_SIZE);
  for(int i = 0; i < MAX_GRAPH_SIZE; i++) {
    graph[i] = (int*) malloc(sizeof(int) * MAX_GRAPH_SIZE);
  }

  cleanGraph(graph, MAX_GRAPH_SIZE);

  for(int curr = 1; curr <= testCases; curr++) {
    int V, E;
    cin >> V;
    cin >> E;

    for(int i = 0; i < E; i++) {
      char first, second;
      cin >> first;
      cin >> second;

      graph[letterToIndex(first)][letterToIndex(second)] = 1;
      graph[letterToIndex(second)][letterToIndex(first)] = 1;
    }

    cout << "Case #" << curr << ":" << endl;

    int amount = connectedComponents(graph, V);

    cout << amount << " connected components" << endl;
    cout << endl;

    cleanGraph(graph, MAX_GRAPH_SIZE);
  }

  return 0;
}