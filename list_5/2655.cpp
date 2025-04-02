#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

#define MAXN 100000
#define MAXM 50

int n, q, m;
std::bitset<MAXM> t[4 * MAXN]; // Segment tree array of bitsets

void build(int a[], int v, int tl, int tr) {
  if (tl == tr) {
    std::bitset<MAXM> monsterPresence;
    monsterPresence.set(a[tl] - 1);
    t[v] = monsterPresence;
  } else {
    int tm = (tl + tr) / 2;
    build(a, v*2, tl, tm);
    build(a, v*2+1, tm+1, tr);
    t[v] = t[v*2] | t[v*2+1];
  }
}

std::bitset<MAXM> query(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return std::bitset<MAXM>(); // Return an empty bitset if the range is invalid
  }
  if (l == tl && r == tr) {
    return t[v]; // Return the bitset corresponding to the current segment
  }
  int tm = (tl + tr) / 2;
  return query(v * 2, tl, tm, l, std::min(r, tm)) |
          query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
}

void update(int v, int tl, int tr, int pos, int new_val) {
  if (tl == tr) {
    std::bitset<MAXM> monsterPresence;
    monsterPresence.set(new_val - 1);
    t[v] = monsterPresence;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm)
      update(v*2, tl, tm, pos, new_val);
    else
      update(v*2+1, tm+1, tr, pos, new_val);
    t[v] = t[v*2] | t[v*2+1];
  }
}


int main() {
  cin >> n >> q >> m;

  int road[n];

  for(int i = 0; i < n; ++i) {
    int monster;
    cin >> monster;

    road[i] = monster;
  }

  build(road, 1, 0, n - 1);

  for(int i = 0; i < q; ++i) {
    int option;
    cin >> option;

    if(option == 2) { // Update
      int coord, newType;
      cin >> coord >> newType;

      update(1, 0, n - 1, coord - 1, newType);
    } else { // Query
      int L, R;
      cin >> L >> R;

      std::bitset<MAXM> seeingMonsters = query(1, 0, n - 1, L - 1, R - 1);

      cout << seeingMonsters.count() << endl;
  }
 }
}