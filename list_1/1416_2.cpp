#include <bits/stdc++.h>
#include <string>

#define INF 3000

using namespace std;

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

auto sortWithTemplateVector(vector<int> templateVector) { 
  return [templateVector](int a, int b) -> bool { return templateVector[a] < templateVector[b]; };
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int teams, num_probs;
    while (cin >> teams >> num_probs && (teams != 0 || num_probs != 0))
    {
        int qntSolved = 0;
        vector<vector<char>> problems(num_probs + 1, vector<char>());
        vector<int> teams_penal(teams + 1, 0);
        vector<int> teams_attempts(teams + 1, 0);
        for (int i = 0; i < teams; i++) {
            int tries = 0;
            string min;
            char bar;
            for (int j = 0; j < num_probs; j++)
            {
                cin >> tries >> bar >> min;
                if (min == "-") continue;
                
                teams_penal[i] += stoi(min);
                teams_attempts[i] += tries - 1;
                qntSolved++;
                
            }
            teams_penal[i] += 20 * teams_attempts[i];
            problems[qntSolved].push_back(i);
            qntSolved = 0;
        }

        int min_penal = 1, max_penal = INF;
        for (int i = 0; i <= num_probs; i++)
        {
            if (problems[i].size() == 0) continue;

            sort(problems[i].begin(), problems[i].end(), sortWithTemplateVector(teams_penal));

            for (int j = 1; j < problems[i].size(); j++)
            {
                int t1 = problems[i][j - 1];
                int t2 = problems[i][j];
                if (teams_attempts[t1] == teams_attempts[t2])
                {
                    continue;
                }
                else if (teams_penal[t1] == teams_penal[t2])
                {
                    min_penal = max_penal = 20;
                }
                else
                {
                    int penal_diff = teams_penal[t2] - teams_penal[t1];
                    int attempt_diff = teams_attempts[t1] - teams_attempts[t2];
                    while (penal_diff <= attempt_diff * (min_penal - 20))
                        min_penal++;
                    while (penal_diff <= attempt_diff * (max_penal - 20))
                        max_penal--;
                }
            }
        }

        cout << min_penal;
        if (max_penal == INF)
            cout << " *\n";
        else
            cout << " " << max_penal << "\n";
    }

    return 0;
}