#include <iostream>
#include <string>

using namespace std;

#define ctoi(c) (c - '0')
 
int main() {
  string N;
  cin >> N;

  // division by 3 is used because the first player can always control the game
  // so the intermediary choices sums 3
  int acc = 0;
  for(size_t i = 0; i < N.size(); i++) {
    int accUntilNow = acc * 10; // since we're going left right in the number, the rest of the last number would need to be summed 10 times
    acc = (accUntilNow + ctoi(N[i])) % 3;
  }

  cout << acc << endl;

  return 0;
}