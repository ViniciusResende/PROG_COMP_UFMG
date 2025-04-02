#include <iostream>
#include <map>
#include <string>
 
using namespace std;
 
int main() {
  std::map<std::string, int> hashMap;
  std::string jewel;

  while(cin >> jewel) {
    if(hashMap.find(jewel) != hashMap.end())
      hashMap[jewel] += 1;
    else
      hashMap[jewel] = 1;
  }

  std::cout << hashMap.size() << std::endl;

  return 0;
}