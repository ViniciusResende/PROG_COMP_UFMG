#include <iostream>
#include <algorithm> 
#include <vector>
#include <string>
#include <sstream>
 
using namespace std;

int findDuplicate(vector<int> a, vector<int> b) {
  a.insert(a.end(), b.begin(), b.end());
  sort(a.begin(), a.end()); // maximum size of a is 20, so O(nlogn) is acceptable
  
  for(int i = 0; i < a.size() - 1; i++) {
    if(a[i] == a[i+1]) return a[i];
  }

  return -1;
}

vector<int> findOccurrences(vector<string> source, string target) {
  vector<int> occurrences;
  auto it = find(source.begin(), source.end(), target);

  while(it != source.end()) {
    occurrences.push_back(it - source.begin());
    it = find(it + 1, source.end(), target);
  }

  return occurrences;
}

int main() {
  vector<vector<string>> table(3);
  table[0] = {".*", "*." , "*.", "**", "**", "*.", "**", "**", "*.", ".*"};
  table[1] = {"**", ".." , "*.", "..", ".*", ".*", "*.", "**", "**", "*."};
  table[2] = {"..", ".." , "..", "..", "..", "..", "..", "..", "..", ".."}; // not necessary

  int inputSize = 0;
  char inputType;
  string input;
  do {
    cin >> inputSize;
    if(inputSize == 0) break;
    
    cin >> inputType;
    if(inputType == 'S') {
      cin >> input;
      for(int i = 0; i < 3; i++) {
        for(int j = 0; j < inputSize; j++) {
          int digit = input.at(j) - '0';
          cout << table[i][digit];
          if(j != inputSize - 1) cout << " ";
        }
        cout << endl;
      }
    } else {
      vector<vector<int>> occurrenceMatrix(inputSize);
      ostringstream ss;   
      for(int i = 0; i < 3; i++) {
        for(int j = 0; j < inputSize; j++) {
          cin >> input;
          if(i != 2) {
            vector<int> occurrenceVector = findOccurrences(table[i], input);
            if(occurrenceMatrix[j].size() == 0) {
              occurrenceMatrix[j] = occurrenceVector;
            } else {
              ss << findDuplicate(occurrenceMatrix[j], occurrenceVector);
            }
          }
        }
      }
      cout << ss.str() << endl;
    }


  } while(inputSize != 0);

  return 0;
}