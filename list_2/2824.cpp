#include <iostream>
#include <string>

using namespace std;

#define MAX_STRING_LEN 5001
string search, article;
int searchSize, articleSize;

int ranker(int searchBegin, int articleBegin, int** DP) {
  if (DP[searchBegin][articleBegin] != -1) return DP[searchBegin][articleBegin];
  if (searchBegin == searchSize || articleBegin == articleSize) return 0;

  if (search[searchBegin] != article[articleBegin]) {
    int ignoreSearchLetter = ranker(searchBegin + 1, articleBegin, DP);
    int ignoreArticleLetter = ranker(searchBegin, articleBegin + 1, DP);

    DP[searchBegin][articleBegin] = max(ignoreSearchLetter, ignoreArticleLetter);
    return DP[searchBegin][articleBegin];
  }  

  DP[searchBegin][articleBegin] = ranker(searchBegin + 1, articleBegin + 1, DP) + 1;
  return DP[searchBegin][articleBegin];
}

int main() {
  int** DP = (int**) malloc(sizeof(int*) * MAX_STRING_LEN);
  for(int i = 0; i < MAX_STRING_LEN; i++) {
    DP[i] = (int*) malloc(sizeof(int) * MAX_STRING_LEN);
    for(int j = 0; j < MAX_STRING_LEN; j++) {
      DP[i][j] = -1;
    }
  }
  cin >> search;
  cin >> article;

  searchSize = search.size();
  articleSize = article.size();

  cout << ranker(0, 0, DP) << endl;

  return 0;
}