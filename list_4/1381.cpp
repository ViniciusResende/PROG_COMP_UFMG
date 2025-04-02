#include <cmath>
#include <iostream>

using namespace std;

#define MOD 1300031

/**
 * Calculates the factorial of a given number.
 *
 * @param n The number for which the factorial is to be calculated.
 * @return The factorial of the given number.
 */
long long factorialMod(int n) {
  long long result = 1;
  for (int i = 2; i <= n; ++i) {
    result = (result * i) % MOD;
  }
  return result;
}


/**
 * Calculates the modular inverse of a number. (Fermat's Little Theorem)
 *
 * This function calculates the modular inverse of a given number `a` with respect to a modulus `m`.
 * The modular inverse of `a` is the number `x` such that (a * x) % m = 1.
 *
 * @param a The number for which the modular inverse is to be calculated.
 * @param m The modulus.
 * @return The modular inverse of `a` with respect to `m`.
 */
long long modInverse(long long a, int m) {
  long long result = 1;
  long long power = m - 2;
  while (power) {
    if (power % 2) {
      result = (result * a) % m;
    }
    a = (a * a) % m;
    power /= 2;
  }
  return result;
}

/**
 * Calculates the combination of 'n' items taken 'k' at a time (n choose k).
 * 
 * @param n The total number of items.
 * @param k The number of items to be taken at a time.
 * @return The number of combinations.
 */
long long combination(int n, int k) {
  if (k > n) return 0;
  long long numerator = factorialMod(n);
  long long denominator = (factorialMod(k) * factorialMod(n - k)) % MOD;
  return (numerator * modInverse(denominator, MOD)) % MOD;
}

/**
 * Counts the number of solutions for a given equation.
 *
 * This function calculates the number of solutions for a given equation
 * using the combination formula.
 *
 * @param N The number of variables in the equation.
 * @param C The number of constants in the equation.
 * @return The number of solutions for the equation.
 */
long long countSolutions(int N, int C) {
  return combination(C + N - 1, N - 1);
}

int main() {
  int testCases;
  cin >> testCases;
  while (testCases--) {
    int N, C;
    cin >> N >> C;

    cout << countSolutions(N, C) << endl;
  }

  return 0;
}