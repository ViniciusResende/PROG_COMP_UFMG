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

  long n = 0, k = 0;
  cin >> n >> k;

  long as[n], bs[n];
  for(long i = 0; i < n; i++){
    long a;
    cin >> a;
    as[i] = a;
  }

  for(long i = 0; i < n; i++){
    long b;
    cin >> b;
    bs[i] = b;
  }

  long min = 99999999999999;
  long teamsPerShirt[n];
  for(long i = 0; i < n; i++){
    teamsPerShirt[i] = bs[i]/as[i];

    if(teamsPerShirt[i] < min) min = teamsPerShirt[i];
  }
  while(k > 0) {
    for(long i = 0; i < n; i++){
      if(teamsPerShirt[i] == min) {
        if(as[i] == 1) {
          teamsPerShirt[i] += k;
          k = -1;
        } else {
          if(bs[i] < as[i]) {
            k -= as[i] - bs[i];
          } else if(bs[i] > as[i] && bs[i] % as[i] != 0) {
            k -= bs[i] % as[i];
          }
        }
        if(k > 0) teamsPerShirt[i]++;
        else {
          if(k == 0) teamsPerShirt[i]++;
          cout << teamsPerShirt[i] << endl;
          exit(0);
        }
      }
    }
    min = 99999999999999;
    for(long i = 0; i < n; i++){
      if(teamsPerShirt[i] < min) min = teamsPerShirt[i];
    }
  }

	exit(0);
}
