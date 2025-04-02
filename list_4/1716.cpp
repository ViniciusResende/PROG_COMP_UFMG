#include <iostream>
#include <cmath>

using namespace std;

// Reference: https://leimao.github.io/article/RSA-Algorithm/

/**
 * Calculates the greatest common divisor (GCD) of two integers using the Euclidean algorithm.
 *
 * @param E The first integer.
 * @param phi The second integer.
 * @return A pair of integers representing the GCD and the coefficients of Bézout's identity.
 */
pair<int, int> gcd(int E, int phi) {
  if (phi == 0) return make_pair(1, 0);

  pair<int, int> np = gcd(phi, E % phi);

  return make_pair(np.second, np.first - (np.second * (E / phi)));
}

int getPhi(int n) {
  int phi = n;
  int primeThreshold = sqrt(n);
  for (int i = 2; i <= primeThreshold; i++) {
    if (n % i == 0)  {
      phi -= phi / i;

      while (n % i == 0) n /= i;
    }
  }

  if (n > 1)  phi -= phi / n;
  return phi;
}

int getExponentialMod(int n, int exp, int mod) {
  int result = 1;

  while (exp > 0) {
    if (exp % 2 == 1) {
      result = ((long long)result * n % mod);
    }
    n = ((long long)n * n % mod);
    exp /= 2;
  }

  return result;
}

int main() {
  int N, E, cryptograph;
  cin >> N;
  cin >> E;
  cin >> cryptograph;

  int D;
  for (int i = 3;; i += 2) {
    if (N % i == 0) {
      int P = i;
      int Q = N / P;
      int totiente = (P - 1) * (Q - 1);
      int phi = getPhi(totiente);
      D = getExponentialMod(E, phi - 1, totiente);
      break;
    }
  }

  int originalMsg = getExponentialMod(cryptograph, D, N);
  cout << originalMsg << endl;

  return 0;
}