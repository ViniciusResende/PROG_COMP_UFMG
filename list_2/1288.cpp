#include <iostream>

using namespace std;

int main() {
  int testsCases;
  cin >> testsCases;
  while(testsCases) {
    int cannonBalls;
    cin >> cannonBalls;
    int damage[cannonBalls], weight[cannonBalls];
    for(int ballIdx = 0; ballIdx < cannonBalls; ballIdx++) 
      cin >> damage[ballIdx] >> weight[ballIdx];

    int cannonCapacity;
    cin >> cannonCapacity;
    int castleResistance;
    cin >> castleResistance;

    // dp
    int DP[cannonBalls + 1][cannonCapacity + 1];
    for(int i = 0; i <= cannonBalls; i++) DP[i][0] = 0;
    for(int i = 0; i <= cannonCapacity; i++) DP[0][i] = 0;

    for(int ball = 1; ball <= cannonBalls; ball++) {
      for(int c = 1; c <= cannonCapacity; c++) {
        if(c < weight[ball - 1]) {
          DP[ball][c] = DP[ball - 1][c];
          continue;
        }

        int bestWithBall = DP[ball - 1][c - weight[ball - 1]] + damage[ball - 1];
        int bestWithoutBall = DP[ball - 1][c];
        DP[ball][c] = max(bestWithBall, bestWithoutBall);
      }
    }

    if(castleResistance > DP[cannonBalls][cannonCapacity]) cout << "Falha na missao\n";
    else cout << "Missao completada com sucesso\n";
  
    testsCases--;
  }

  return 0;
}