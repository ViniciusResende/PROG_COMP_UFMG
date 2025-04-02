#include <iostream>
#include <vector>

using namespace std;

long long countSeqs(vector<int> &nums, int numbersAmount, int seqSize) {
  long long count = 0;
  vector<vector<long long>> dp(numbersAmount, vector<long long>(seqSize, 0));

  for(int i = 0; i < numbersAmount; i++) dp[i][0] = 1;

  for(int i = 1; i < numbersAmount; i++) {
    for(int j = 1; j <= i && j < seqSize; j++) {
      for(int k = 0; k < i; k++) {
        if(nums[k] < nums[i]) dp[i][j] += dp[k][j - 1];
      }
    }
  }

  for (int i = 0; i < numbersAmount; i++) count += dp[i][seqSize - 1];

  return count;
}

int main(){
  while(1) {
    short numbersAmount, seqSize;
    cin >> numbersAmount;
    if(numbersAmount == 0) break;
    vector<int> numbers(numbersAmount);

    cin >> seqSize;
    
    for(int i = 0; i < numbersAmount; i++) {
      int temp;
      cin >> temp;
      numbers[i] = temp;
    }

    cout << countSeqs(numbers, numbersAmount, seqSize) << endl;
  }

  return 0;
}