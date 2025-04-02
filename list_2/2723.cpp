#include <iostream>
#include <vector>

using namespace std;

bool verifyWeight(const vector<int>& weights, int diff, int currGift){
  if(weights.size() == 0) return true;
  if(weights.size() == 1) return weights[0] <= 5;

  int currDiff = abs(diff - weights[currGift]);
  if(currGift == weights.size() - 1) { // last gift
    return (weights[currGift] + diff <= 5) || (currDiff <= 5);
  } else if(
    weights[currGift] + diff <= 5 &&
    verifyWeight(weights, weights[currGift] + diff, currGift + 1)
  ) { // gift can be added to curr stack
    return true;
  } else if (
    currDiff <= 5 &&
    verifyWeight(weights, currDiff, currGift + 1)
  ) {
    return true;
  }

  return false;
}

int main() {
  int testCases;
  cin >> testCases;
  while(testCases--) {
    int giftsAmount;
    cin >> giftsAmount;

    vector<int> weights(giftsAmount);
    for(int i = 0; i < giftsAmount; i++) cin >> weights[i];

    if(verifyWeight(weights, 0, 0)) cout << "Feliz Natal!" << endl;
    else cout << "Ho Ho Ho!" << endl;
  }

  return 0;
}