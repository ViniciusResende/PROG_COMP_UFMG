#include <iostream>
#include <string>
#include <vector>

#define INF 0x3f3f3f3f
#define max(a,b) (a>b)?(a):(b)

int main() {
  int amountOfBags, amountOfCompetitors, fullestBag = 0;
  double popcornPerSec = 0.0;
  std::cin >> amountOfBags; 
  std::cin >> amountOfCompetitors;
  std::cin >> popcornPerSec;

  std::vector<int> bags;
  for(int i = 0; i < amountOfBags; i++) {
    int curr;
    std::cin >> curr;
    bags.push_back(curr);
    fullestBag = max(fullestBag, bags[i]);
  }

  int ss = 1, answer = INF;
  bool solutionFound = false;
  int fullestBagTime = fullestBag / popcornPerSec;
  int emptiestBagTime = fullestBagTime / 2;
  while(ss != 0) {
    int competitor = 0, bag = 0;;
    for(int i = 0; i < amountOfBags; i++) {
      if((bags[i] / popcornPerSec) > fullestBagTime || competitor == amountOfCompetitors) {
        competitor = amountOfCompetitors + 1;
        break;
      }

      if ((bag + bags[i]) / popcornPerSec <= fullestBagTime) { // Competitor can fit bag
        bag += bags[i];
        continue;
      }

      bag = bags[i];
      competitor++;
    }

    ss = (fullestBagTime - emptiestBagTime) / 2;
    competitor++;
    
    if (competitor <= amountOfCompetitors) {
      answer = fullestBagTime;
      fullestBagTime -= ss;
      solutionFound = true;
      continue;
    }
    if (solutionFound) {
      emptiestBagTime = fullestBagTime;
      fullestBagTime += ss;
      continue;
    }

    ss = 1;
    emptiestBagTime = fullestBagTime;
    fullestBagTime = fullestBagTime * 2;
  }

  std::cout << answer << std::endl;

  return 0;
}