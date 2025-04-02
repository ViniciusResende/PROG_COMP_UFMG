#include <algorithm>
#include <iostream>
#include <map>
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
  int maxMatchesPerEach = 4;
  int pointsPerWin = 2;
  while (1) {
    int teams, matchesPerEach, alreadyPlayed, maxMatchesPerEach = 4;
    cin >> teams;
    cin >> matchesPerEach;
    cin >> alreadyPlayed;

    if(teams == 0 && matchesPerEach == 0 && alreadyPlayed == 0) break;

    int team1, team2, teamZeroGamesPlayed = 0;
    char result;
    vector<vector<int>> gamesPlayed(teams + 1, vector<int>(teams + 1, 0));
    vector<int> pointsPerTeam(teams + 1, 0);
    for (int i = 0; i < alreadyPlayed; i++) {
      cin >> team1 >> result >> team2;

      gamesPlayed[team1][team2]++;
      gamesPlayed[team2][team1]++;

      if (team1 == 0 || team2 == 0) teamZeroGamesPlayed++;
      if (result == '=') {
        pointsPerTeam[team1]++;
        pointsPerTeam[team2]++;
        continue;
      }      
      pointsPerTeam[team2] += pointsPerWin;
    }

    int gamesToBePlayedPerTeam = (teams - 1) * matchesPerEach;
    int maxReachablePoints = pointsPerTeam[0] + ((gamesToBePlayedPerTeam - teamZeroGamesPlayed) * pointsPerWin) - 1;
    bool myTeamCanReachMoreThanCurrFirstTeam = true;
    for (int i = 1; i < teams; i++) {
      if (maxReachablePoints < pointsPerTeam[i]) {
        myTeamCanReachMoreThanCurrFirstTeam = false;
        cout << "N" << endl;
        break;
      }
    }
    if (!myTeamCanReachMoreThanCurrFirstTeam) continue;

    map<pair<int, int>, int> matchPlayedBetweenStep;
    int graphFlowStep = teams;
    int sumOfAllOtherTeamsToGetTheWin = 0;
    for (int i = 1; i < teams; i++) {
      for (int j = i + 1; j < teams; j++){
        sumOfAllOtherTeamsToGetTheWin += (matchesPerEach - gamesPlayed[i][j]) * pointsPerWin;
        matchPlayedBetweenStep[make_pair(i, j)] = graphFlowStep;
        graphFlowStep++;
      }
    }

    int src = 0, tgt = graphFlowStep + 1;
    Graph graph(graphFlowStep + 2, src, tgt);
    
    for (int i = 1; i < teams; i++) {
      for (int j = i + 1; j < teams; j++) {
        int matchesPlayed = matchPlayedBetweenStep[make_pair(i, j)];

        graph.addEdge(i, matchesPlayed, INF);
        graph.addEdge(j, matchesPlayed, INF);
        graph.addEdge(matchesPlayed, tgt, (matchesPerEach - gamesPlayed[i][j]) * pointsPerWin);
      }
    }

    for (int i = 1; i < teams; i++) {
      graph.addEdge(src, i, maxReachablePoints - pointsPerTeam[i]);
    }

    int maxFlow = graph.graphMaxFlow();
    cout << ((maxFlow == sumOfAllOtherTeamsToGetTheWin) ? "Y" : "N") << endl;
  }

  return 0;
}