#include <iostream>
#include <cmath>

using namespace std;

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

bool isSuper(int number) {
  int currDigit = number % 10;
  while (number >= 1) {
    if (!isPrime(currDigit)) return false;

    // shifts each digit
    number /= 10;
    currDigit = number % 10; 
  }

  return true;
}

int main() {
  int N;
  while (cin >> N) {
    if (!isPrime(N)) {
      cout << "Nada" << endl;
    } else if (isSuper(N)) {
      cout << "Super" << endl;
    } else {
      cout << "Primo" << endl;
    }
  }

  return 0;
}