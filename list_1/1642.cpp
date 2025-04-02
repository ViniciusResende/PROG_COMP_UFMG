#include <iostream>
#include <map>
#include <string>

int main() {
  int m;
  std::cin >> m;
  while(m) {
    std::string input;
    std::getline(std::cin >> std::ws, input);

    std::map<char, int> occurrenceMap;
    int leftIt = 0, rightIt = 0, best = 0;
    while(rightIt < input.size()) {
      char c = input[rightIt];

      if(occurrenceMap.find(c) == occurrenceMap.end()) occurrenceMap[c] = 1;
      else occurrenceMap[c]++;

      while(occurrenceMap.size() > m) {
        c = input[leftIt];
        occurrenceMap[c]--;
        leftIt++;

        if (occurrenceMap[c] == 0) occurrenceMap.erase(c);
      }

      int slidingWindowSize = rightIt - leftIt + 1;
      best = std::max(best, slidingWindowSize);

      rightIt++;
    }

    std::cout << best << std::endl;
    std::cin >> m;
  }
  return 0;
}