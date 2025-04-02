#include <iostream>
#include <vector>

using namespace std;

#define INTERVAL_THRESHOLD 2000001

/**
 * Preprocesses the quantity of divisors for all possible inputs.
 * It iterates up to INTERVAL_THRESHOLD (2 * 10^6) so that the divisors of numbers which
 * multiplied by 2 are greater than INTERVAL_THRESHOLD are accounted for.
 */
vector<int> getPrimeDivisorNumberCount() {
  vector<int> divisorsNumberList(INTERVAL_THRESHOLD, 0);
  vector<bool> primeList(INTERVAL_THRESHOLD, 1);
  primeList[0] = primeList[1] = 0;

  int aux, factorsCount;
  for (int i = 2; i <= INTERVAL_THRESHOLD; i++) {
    if (primeList[i]) {
      divisorsNumberList[i] = 2; // 1 and the number itself
      for (int j = i * 2; j <= INTERVAL_THRESHOLD; j += i) {
        primeList[j] = 0; // multiple of i isnt prime
        factorsCount = 0, aux = j;
        // gets exponential val for current prime
        while (aux % i == 0) {
          factorsCount++;
          aux /= i;
        }
        // if the number still has other prime factors to be divided by,
        // multiply the current prime factor by 2 to account for
        // all possible exponent combinations
        if (aux != 1)
          factorsCount *= 2;
          
        if (divisorsNumberList[j] == 0)
          divisorsNumberList[j] = factorsCount + 1;
        else
          divisorsNumberList[j] *= (factorsCount + 1); // combination of existing divisors
      }
    }
  }

  vector<int> primeDivisorsNumberCount(INTERVAL_THRESHOLD, 0);
  for (int i = 2; i <= INTERVAL_THRESHOLD; i++) {
    primeDivisorsNumberCount[i] = primeDivisorsNumberCount[i - 1];
    if (primeList[divisorsNumberList[i]])
      primeDivisorsNumberCount[i]++;
  }

  return primeDivisorsNumberCount;
}

int main() {
  vector<int> primeDivisorsNumberCount = getPrimeDivisorNumberCount();

  int selectedNumber;
  while (cin >> selectedNumber)
   cout << primeDivisorsNumberCount[selectedNumber] << endl;

  return 0;
}