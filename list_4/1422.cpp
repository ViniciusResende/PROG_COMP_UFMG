#include <iostream>

using namespace std;

#define MOD 13371337

/**
 * Multiplies two numbers modulo MOD.
 *
 * This function calculates the product of two numbers `a` and `b` modulo MOD.
 * It uses bitwise operations and modular arithmetic to efficiently compute the result.
 *
 * @param a The first number.
 * @param b The second number.
 * @return The product of `a` and `b` modulo MOD.
 */
long long mulMod(long long a, long long b) {
  long long res = 0;
  while (a != 0) {
    if (a & 1) res = ((res % MOD) + (b % MOD)) % MOD;
    a >>= 1;
    b = (b << 1) % MOD;
  }
  return res;
}

/**
 * Calculates the modular exponentiation of a base raised to an exponent.
 *
 * @param base The base value.
 * @param exp The exponent value.
 * @return The result of the modular exponentiation.
 */
long long modPow(int initial, long long base, long long exp) {
  long long result = initial;
  while (exp > 0) {
    if (exp % 2 == 1) {  // If exp is odd, multiply base with result
      result = mulMod(result, base);
    }
    base = mulMod(base, base);  // Square the base
    exp /= 2;
  }
  return result;
}

int main() {
  long long targetDay;
  cin >> targetDay;
  int createdBacteria[4];
  while(targetDay != 0) {
    long long amountOfBacteria = 0;
    for (int i = 0; i < 4; ++i) {
      cin >> createdBacteria[i];
      amountOfBacteria += createdBacteria[i];
    }

    int firstDaysThreshold = min((long long) 4, targetDay - 4);
    for(int i = 0; i < firstDaysThreshold; ++i) {
      amountOfBacteria *= 2;
      amountOfBacteria -= createdBacteria[i];
    }

    targetDay -= 8; 

    if (targetDay > 0) {
      // Efficiently compute the remaining days
      amountOfBacteria = modPow(amountOfBacteria, 2, targetDay) % MOD;
    }

    cout << amountOfBacteria << endl;

    cin >> targetDay;
  }

  return 0;
}