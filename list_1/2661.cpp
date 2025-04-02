#include <iostream>
#include <math.h>

using namespace std;

// isDespojado = !prime && (n % perfectSquareRoot != 0). Which means, no repetition and more than one number
bool isDespojado(long long n){
  bool isPrime = true;
  for(long long i = 2; i <= sqrt(n); i++) {
    if(n % (i*i) == 0) return false;
    if(n % i == 0) isPrime = false;
  }
  
  return !isPrime;
}


int main(){
  int count = 0;
  long long n;
  cin >> n;

  double nSqRoot = sqrt(n);

  // Does not go to <= sqrt(n) to prevent call isDespojado with the same value, when i == n/i
  for(long long i = 1; i < nSqRoot; i++) {
    if(n % i == 0) {
      if(isDespojado(i)) count++;
      if(isDespojado(n/i)) count++; // necessary because, since n / i = x -> n / x = i;
    }
  }

  if((n % (int) nSqRoot == 0) && isDespojado(nSqRoot)) count++;

  cout << count << endl;

  return 0;
}