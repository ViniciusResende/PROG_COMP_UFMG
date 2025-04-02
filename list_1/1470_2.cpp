#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Function to perform folding operation on input vector and check if it matches output vector
bool fold(const vector<int>& input, const vector<int>& output, int offset, bool isRev) {
  vector<int> temp = input;
  while (temp.size() > output.size()) {
    vector<int> folded;
    int j = offset - 1, i = offset;
    while (j >= 0) {
      folded.push_back(temp[j] + temp[i]);
      i++;
      j--;
    }

    for (int k = i; k < temp.size(); k++) {
      folded.push_back(temp[k]);
    }
    temp.clear();
    temp = folded;
    if (temp.size() > output.size() && offset > output.size())
      break;
  }

  if(temp == output) return true;

  reverse(temp.begin(), temp.end());
  return temp == output;
}

// Function to compare input and output vectors after folding
bool assertViability(const vector<int>& input, const vector<int>& output) {
  bool resp = false;
  int si = input.size() / 2;

  for (int k = 1; k <= si; k++) {
    resp = fold(input, output, k, false);
    if (resp) return resp;
  }

  vector<int> reversedInput = input;
  reverse(reversedInput.begin(), reversedInput.end());
  for (int k = 1; k <= si; k++) {
    resp = fold(reversedInput, output, k, true);
    if (resp) return resp;
  }

  return false;
}

// Function to calculate the sum of elements in a vector
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
    for (int i = 0; i < inputSize; i++) {
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

    if (sizeDiff < 0 || (sumVector(input) != sumVector(output))) {
      cout << "N" << endl;
      continue;
    }

    if (sizeDiff == 0) {
        if (input == output) {
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
