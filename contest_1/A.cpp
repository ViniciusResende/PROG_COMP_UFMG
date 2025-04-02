//#include <bits/stdc++.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;
typedef pair<int, int> ii;


int main(){ _
//	char end = '\n';

  int n;
  cin >> n;

  int as[n], bs[n];
  for(int i = 0; i < n; i++){
    int a, b;
    cin >> a >> b;

    as[i] = a;
    bs[i] = b;
  }

  int conflicts = 0;
  for(int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      if(as[i] == bs[j]) conflicts++;
      if(bs[i] == as[j]) conflicts++;
    }
  }

  cout << conflicts << endl;

	exit(0);
}
