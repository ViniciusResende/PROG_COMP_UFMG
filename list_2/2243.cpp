#include <algorithm>
#include <iostream>

#define COLUMNS_THRESHOLD 50001

using namespace std;

int columns[COLUMNS_THRESHOLD], lSide[COLUMNS_THRESHOLD], rSide[COLUMNS_THRESHOLD];

int main() {
  int columnsAmount;
  cin >> columnsAmount;
  for (int i = 0; i < columnsAmount; i++) cin >> columns[i];
  lSide[0] = 1;
  rSide[columnsAmount - 1] = 1;

  for (int i = 1; i < columnsAmount; i++) lSide[i] = min(lSide[i - 1] + 1, columns[i]);

  for (int i = columnsAmount - 2; i >= 0; i--) rSide[i] = min(rSide[i + 1] + 1, columns[i]);

  int pyramidLimiter, maxheight = 0;
  for (int i = 0; i < columnsAmount; i++) {
    pyramidLimiter = min(lSide[i], rSide[i]);
    maxheight = max(maxheight, pyramidLimiter);
  }

  cout << maxheight << "\n";
  return 0;
}