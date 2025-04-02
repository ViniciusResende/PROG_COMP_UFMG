#include <iostream>
#include <string>
 
using namespace std;

int main() {
  std::string message, crib;

  cin >> message;
  cin >> crib;

  int lo = 0, hi = 0, collisions = 0, curr = 0, matches = 0;

  while(hi < message.length()) {
    bool collision = false;
    for(int i = lo; i <= hi; i++) {
      if(message[i] == crib[i - lo]) {
        collision = true;
        break;
      }
    }
    if(collision) lo++;
    else curr++;

    if(curr == crib.length()) {
      cout << "-> " << hi << " " << lo << " " << crib[hi - lo] << " " << message[hi] << std::endl;
      matches++;
      lo++;
      curr--;
    }
    hi++;
  }

  cout << matches << std::endl;

  return 0;
}