#include <iostream>
 
using namespace std;

#define UNDEFINED -1
#define MAX_WEIGHT 50
#define max(a,b) ((a)>(b)?(a):(b))

class KnapSackAnswer {
  public:
    int best, neededWeight, neededPackages;
    bool operator>(const KnapSackAnswer& other) {
      return best > other.best;
    }
};

KnapSackAnswer recursiveKnapSack(int W, int amounts[], int weights[], int idx, KnapSackAnswer** memo) {
  if(idx < 0) return {0,0,0};
  if(memo[idx][W].best != UNDEFINED) return memo[idx][W];

  if(weights[idx] > W) {
    memo[idx][W] = recursiveKnapSack(W, amounts, weights, idx - 1, memo);
    return memo[idx][W];
  } else {
    KnapSackAnswer with = recursiveKnapSack(W - weights[idx], amounts, weights, idx - 1, memo);
    with.best += amounts[idx];
    with.neededWeight += weights[idx];
    with.neededPackages++;

    KnapSackAnswer without = recursiveKnapSack(W, amounts, weights, idx - 1, memo);

    memo[idx][W] = max(with, without);
    return memo[idx][W];
  }
}

KnapSackAnswer knapSack(int amounts[], int weights[], int n) {
  KnapSackAnswer** memo = (KnapSackAnswer**) malloc(sizeof(KnapSackAnswer*)*n);
  for(int i = 0; i < n; i++) {
    memo[i] = (KnapSackAnswer*) malloc(sizeof(KnapSackAnswer) * (MAX_WEIGHT + 1));
  }

  for(int i = 0; i < n; i++)
    for(int j = 0; j <= MAX_WEIGHT; j++)
      memo[i][j] = {UNDEFINED, UNDEFINED, UNDEFINED};
  
  int W = MAX_WEIGHT;

  return recursiveKnapSack(W, amounts, weights, n - 1, memo);
}

int main() {
  int testCases;
  cin >> testCases;

  while(testCases--) {
    int availablePackages;
    cin >> availablePackages;

    int amounts[availablePackages], weights[availablePackages];
    for(int i = 0; i < availablePackages; i++) {
      int a, w;
      cin >> a >> w;
      amounts[i] = a;
      weights[i] = w;
    }

    KnapSackAnswer answer = knapSack(amounts, weights, availablePackages);
    cout << answer.best << " brinquedos" << endl;
    cout << "Peso: " << answer.neededWeight << " kg" << endl;
    cout << "sobra(m) " << availablePackages - answer.neededPackages << " pacote(s)" << endl;
    cout << endl;
  }

  return 0;
}