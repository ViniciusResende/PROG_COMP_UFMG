#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define INF 3000
#define DEFAULT_PENALTY 20

using namespace std;

auto sortWithTemplateVector(vector<int> templateVector) { 
  return [templateVector](int a, int b) -> bool { return templateVector[a] < templateVector[b]; };
}

int main() {
  int teams, problems;
  cin >> teams;
  cin >> problems;
  while (teams && problems) {
    int solvedCount = 0;
    vector<vector<char>> problemsList(problems + 1, vector<char>());
    vector<int> penalty(teams + 1, 0);
    vector<int> attemps(teams + 1, 0);
    for (int i = 0; i < teams; i++) {
      int problemAttempts = 0;
      char slashChar;
      string time;
      for (int j = 0; j < problems; j++) {
        cin >> problemAttempts >> slashChar >> time;

        if (time == "-") continue;
        
        penalty[i] += stoi(time);
        attemps[i] += problemAttempts - 1;
        solvedCount++;
      }
      penalty[i] += DEFAULT_PENALTY * attemps[i];
      problemsList[solvedCount].push_back(i);
      solvedCount = 0;
    }

    int minPenalty = 1, maxPenalty = INF;
    for (int i = 0; i <= problems; i++) {
      if (problemsList[i].size() == 0) continue;

      sort(problemsList[i].begin(), problemsList[i].end(), sortWithTemplateVector(penalty));

      for (int j = 1; j < problemsList[i].size(); j++) {
        int firstTeam = problemsList[i][j - 1];
        int secondTeam = problemsList[i][j];
        if (attemps[firstTeam] == attemps[secondTeam]) continue;
        else if (penalty[firstTeam] == penalty[secondTeam]) minPenalty = maxPenalty = 20;
        else {
          int attempsGap = attemps[firstTeam] - attemps[secondTeam];
          int penaltyGap = penalty[secondTeam] - penalty[firstTeam];
          while (penaltyGap <= attempsGap * (maxPenalty - DEFAULT_PENALTY))
            maxPenalty--;
          while (penaltyGap <= attempsGap * (minPenalty - DEFAULT_PENALTY))
            minPenalty++;          
        }
      }
    }

    cout << minPenalty;
    if (maxPenalty == INF) cout << " *" << endl;
    else cout << " " << maxPenalty << endl;

    cin >> teams;
    cin >> problems;
  }

  return 0;
}