#include <iostream>

#define INF 0x3f3f3f3f
#define LIFE_POINTS_THRESHOLD 2010
#define SPELL_AMOUNT_THRESHOLD 1010

using namespace std;

int dp[LIFE_POINTS_THRESHOLD][SPELL_AMOUNT_THRESHOLD];

int minManaSpent(int *damage, int *manaCost, int currentHP, int currSpell, int last_idx) {
  if (currentHP <= 0)  return 0;
  if (dp[currentHP][currSpell] != -1) return dp[currentHP][currSpell];
  if (currSpell == last_idx) return INF;

  int notUsingCurrSpell = minManaSpent(damage, manaCost, currentHP, currSpell + 1, last_idx);
  int usingCurrSpell = minManaSpent(damage, manaCost, currentHP - damage[currSpell], currSpell + 1, last_idx) + manaCost[currSpell];

  dp[currentHP][currSpell] = min(notUsingCurrSpell, usingCurrSpell);
  
  return dp[currentHP][currSpell];
}

int main() {
  int N, P;
  while(cin >> N >> P) {
    int damage[N], manaCost[N];
    for(int i = 0; i < N; i++) cin >> damage[i] >> manaCost[i];

    for(int i = 0; i < LIFE_POINTS_THRESHOLD; i++) {
      for(int j = 0; j < SPELL_AMOUNT_THRESHOLD; j++) 
        dp[i][j] = -1;
    }

    int manaSpent = minManaSpent(damage, manaCost, P, 0, N);
    cout << ((manaSpent != INF) ? (manaSpent) : -1) << endl;
  }

  return 0;
}