#include <iostream>
#include <math.h>

using namespace std;

const int mod = 1e9 + 7;

long long sumDigitsUntil(long long num) {
  if (num < 10) return (num * (num + 1)) / 2;

  long long digitsAmount = log10(num);
  long long sumPerDigit[digitsAmount + 1];
  sumPerDigit[1] = 45;

  for (long long i = 2; i <= digitsAmount; i++) {
    sumPerDigit[i] = (sumPerDigit[i - 1] * 10) + (45 * pow(10, i - 1));
  }

  long long digitsPowered = pow(10, digitsAmount);
  long long leftMostDigit = num / digitsPowered;

  long long sumOfTheMostSignificative = (num % digitsPowered + 1) * leftMostDigit;
  long long sumUntilRoundedMostSignificative = (sumPerDigit[digitsAmount] * leftMostDigit) + ((leftMostDigit * (leftMostDigit - 1)) / 2) * digitsPowered;
  long long remainder = sumDigitsUntil(num % digitsPowered);

  return sumOfTheMostSignificative + sumUntilRoundedMostSignificative + remainder;
}

int main() {
  long long total, left, right;
  while(cin >> left >> right) {
    total = sumDigitsUntil(right) - sumDigitsUntil(left - 1);
    cout << total % mod << endl;
  }

  return 0;
}