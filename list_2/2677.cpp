#include <iostream>

#define NUMBER_RANGE_THRESHOLD 1002

using namespace std;

int input[NUMBER_RANGE_THRESHOLD], DP[NUMBER_RANGE_THRESHOLD][NUMBER_RANGE_THRESHOLD];

int main() {
  int oddNumbers;

  while(1) {
    cin >> oddNumbers;
    if(oddNumbers == 0) break;

    int totalNumbers = oddNumbers * 2;
    for(int i = 0; i < totalNumbers; i++) cin >> input[i];

    for(int i = 1; i < totalNumbers; i++) {
      for(int j = 0; i + j < totalNumbers; j++) {
        int k = i + j;

        if(i % 2 == 0) DP[j][k] = min(DP[j][k - 1], DP[j + 1][k]);
        else
          DP[j][k] = max(DP[j][k - 1] + !(input[k] % 2), DP[j + 1][k] + !(input[j] % 2));
      }
    }

    cout << DP[0][totalNumbers - 1] << endl;
  }

  return 0;
}