#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N, Q, M;
  cin >> N >> Q >> M;

  vector<int> road(N);

  for(int i = 0; i < N; ++i) {
    int monster;
    cin >> monster;

    road[i] = monster;
  }

  for(int i = 0; i < Q; ++i) {
    int option;
    cin >> option;

    if(option == 2) {
      int coord, newType;
      cin >> coord >> newType;

      road[coord - 1] = newType;
    } else {
      int L, R;
      cin >> L >> R;

      int count = 0;
      vector<bool> seenMonsters(M, false);
      for(int j = L - 1; j < R; ++j) {
        if(!seenMonsters[road[j] - 1]) {
          seenMonsters[road[j] - 1] = true;
          count++;
        }
      }

      cout << count << endl;
    }
  }

  return 0;
}