#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef vector<unsigned long long> long_vector;
typedef vector<long_vector> long_matrix;

long_matrix naiveMultiplication(long_matrix x, long_matrix y) {
  long_matrix result(x.size(), long_vector(y[0].size(), 0));
  for (int i = 0; i < x.size(); i++) {
    for (int j = 0; j < y[0].size(); j++) {
      for (int k = 0; k < y.size(); k++) {
        result[i][j] += (x[i][k] % 1000000) * (y[k][j] % 1000000);
        result[i][j] = result[i][j] % 1000000;
      }
    }
  }
  return result;
}

long_matrix matrixPow(long_matrix x, unsigned long long exp) {
  if (exp == 0) return long_matrix{{1, 0}, {0, 1}};

  long_matrix result = matrixPow(x, exp / 2);
  result = naiveMultiplication(result, result);

  if (exp % 2 == 1) result = naiveMultiplication(result, x);

  return result;
}

int main() {
  unsigned long long N, K, L;
  while (cin >> N >> K >> L) {
    N = N / 5;
    long_matrix microBus = {{1, K}};
    long_matrix allBus = {{0, L}, {1, K}};

    long_matrix allBusPow = matrixPow(allBus, N);

    cout << setw(6) << setfill('0');
    cout << (naiveMultiplication(microBus, allBusPow)[0][0] % 1000000) << endl;
  }

  return 0;
}