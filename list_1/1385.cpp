#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

typedef pair<int, int> iPair;
typedef priority_queue<iPair, vector<iPair>, greater<iPair>> min_heap; 

int personsOffset[100], outMatrix[100][100];

int charToInt(char c) { return c - '0';}

int fulfillOutMatrix(string prices[], int personIdx, int colIdx, int accumulator, int lastPersonIdx, int colsSize) {
  if (colIdx < colsSize) {
    int charIterator = personsOffset[personIdx], numIter;
    if (personIdx == lastPersonIdx + 1) numIter = (int)prices[personIdx].size();
    else numIter = min(personsOffset[personIdx] + 3, (int)prices[personIdx].size());

    int acc = 0;
    for (int i = personsOffset[personIdx]; i < numIter; i++) {
      acc = (acc * 10) + charToInt(prices[personIdx][i]);
      personsOffset[personIdx] = i + 1;
      outMatrix[personIdx][colIdx] = acc;

      if ((personIdx < (lastPersonIdx + 1)) && fulfillOutMatrix(prices, personIdx + 1, colIdx, accumulator + acc, lastPersonIdx, colsSize)) return 1;
      else if (personIdx == lastPersonIdx + 1) {
        if (accumulator == acc && fulfillOutMatrix(prices, 1, colIdx+1, 0, lastPersonIdx, colsSize)) return 1;
        if (acc > accumulator) {
          personsOffset[personIdx] = charIterator;
          break;
        }
      }

      personsOffset[personIdx] = charIterator;

      if (prices[personIdx][charIterator] == '0') break;
    }
  } else {
    int val = 0, acc = 0;
    for (int i = personsOffset[personIdx]; i < (int)prices[personIdx].size(); i++) val = (val * 10) + charToInt(prices[personIdx][i]);
    for (int i = 0; i < colsSize; i++) acc += outMatrix[personIdx][i];

    if (acc != val) return 0;
    outMatrix[personIdx][colIdx] = val;
    if (personIdx == lastPersonIdx + 1) return 1;
    else return fulfillOutMatrix(prices, personIdx + 1, colIdx, accumulator, lastPersonIdx, colsSize);
  }

  return 0;
}

int main() {
  int C, i, j;
  cin >> C;
  for (i = 0; i < C; i++) {
    int lineIdx = 0;
    string lines[100];
    string names[100];
    string prices[100];

    while (cin >> lines[lineIdx]) {
      if (lines[lineIdx].rfind("TP", 0) == 0) break;
      if (lineIdx > 0) {
        string name = "";
        for (j = 0; j < lines[lineIdx].size(); j++){
          char c = lines[lineIdx][j];
          if (isalpha(c)) name.push_back(c);
          else {
            names[lineIdx] = name;
            break;
          }
        }
        for (;j < lines[lineIdx].size(); j++) prices[lineIdx].push_back(lines[lineIdx][j]);
      }
      lineIdx++;
      prices[lineIdx] = "";
    }
    for (j = 2; j < lines[lineIdx].size(); j++) prices[lineIdx].push_back(lines[lineIdx][j]); // for TP line

    int totalsLength = 6;
    int charsPerProductHeader = 2;
    int colsSize = (lines[0].size() - totalsLength) / charsPerProductHeader;
    int lastPersonIdx = lineIdx - 1;

    memset(outMatrix, 0, sizeof(outMatrix));
    memset(personsOffset, 0, sizeof(personsOffset));
    fulfillOutMatrix(prices, 1, 0, 0, lastPersonIdx, colsSize);

    // Header
    for (int k = 0; k < colsSize; k++) cout << "P" << k + 1 << " ";
    cout << "Totals" << endl;

    // Products per person
    for (j = 1; j < lineIdx; j++) {
      cout << names[j];
      for (int k = 0; k <= colsSize; k++){
        cout << " " << outMatrix[j][k];
      }
      cout << endl; 
    }

    // Total
    cout << "TP";
    for (int k = 0; k <= colsSize; k++){
      cout << " " << outMatrix[j][k];
    }
    cout << endl;
  }

  return 0;
}