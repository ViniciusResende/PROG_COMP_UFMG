#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

#define MAX 1000000000

/**
 * Checks if a given number is prime.
 * 
 * @param number The number to be checked.
 * @return True if the number is prime, false otherwise.
 */
bool isPrime(unsigned int number) {
  if (number == 2) return true;
  if (number <= 1 || number % 2 == 0) return false;

  int primeThreshold = sqrt(number);
  for (int i = 3; i <= primeThreshold; i += 2) {
    if (number % i == 0) return false;
  }

  return true;
}

int main(){
  int numberOfTests;
  cin >> numberOfTests;
  while (numberOfTests--) {
    unsigned int initialListSize;
    cin >> initialListSize;

    vector<unsigned int> initialList(initialListSize, 0);
    for (unsigned int i = 0; i < initialListSize; i++)
      cin >> initialList[i];

    // sort ascending
    sort(initialList.begin(), initialList.end());

    // remove duplicated numbers
    initialList.erase(unique(initialList.begin(), initialList.end()), initialList.end());

    if (initialList[0] != 1) { // early exit if not begin with 1
      cout << "0" << endl;
      continue;
    }

    unsigned int greatestPrimeOnSequence, currentNumber = 1, it = 0; 
    while (currentNumber <= MAX) {
        bool isInList = initialList[it] == currentNumber;
        // found prime that isnt in the number list
        if (!isInList && isPrime(currentNumber))  {
          greatestPrimeOnSequence = currentNumber;
          break;
        }

        // number not on the list, but can be made from multiplying other numbers
        if (!isInList) {
          currentNumber++;
          continue;
        }

        // number on the list
        currentNumber++;
        it++;
    }

    cout << greatestPrimeOnSequence - 1 << endl;
  }

  return 0;
}