#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool fold(vector<int> input, vector<int> output, int placement) {
  vector<int> temp = input;
  while (temp.size() > output.size()) {
    int j = placement - 1, i = placement;
    vector<int> folded(placement);
    while (j >= 0) {
      folded[j] = temp[j] + temp[i];
      i++;
      j--;
    }

    for (int k = i; k < temp.size(); k++) folded.push_back(temp[k]);
    
    temp.clear();
    temp = folded;
    if (placement > output.size()) break;
  }

  if(temp == output) return true;

  reverse(temp.begin(), temp.end());
  return temp == output;
}

bool assertViability(vector<int> input, vector<int> output) {
  for (int k = 1; k < input.size(); k++) {
    bool ans = fold(input, output, k);
    if (ans)
      return ans;
  }

  return false;
}

int sumVector(vector<int> vec) {
  int sum_of_elems = 0;
  for (auto& n : vec) sum_of_elems += n;
  return sum_of_elems;
}

int main() {
  int inputSize;
  while (cin >> inputSize) {
    vector<int> input(inputSize);
    int element;
    for (int i = 0; i < inputSize; i++)  {
      cin >> element;
      input[i] = element;
    }

    int outputSize;
    cin >> outputSize;
    vector<int> output(outputSize);
    for (int i = 0; i < outputSize; i++) {
      cin >> element;
      output[i] = element;
    }

    int sizeDiff = inputSize - outputSize;
    // discard if sum is not the same 
    if (sizeDiff < 0 || (sumVector(input) != sumVector(output))) {
      cout << "N" << endl;
      continue;
    }


    // if same size they need to be equal or inverted fold on the beginning or in the end of the vector
    if (sizeDiff == 0) { 
      if (input == output)  {
        cout << "S" << endl;
        continue;
      }

      bool everyCharMatch = true;
      for (int i = 0; i < outputSize; i++) {
        if (input[i] != output[outputSize - 1 - i])
          everyCharMatch = false;
      }

      cout << (everyCharMatch ? "S" : "N") << endl;
      continue;
    }

    cout << (assertViability(input, output) ? "S" : "N") << endl;
  }
  return 0;
}