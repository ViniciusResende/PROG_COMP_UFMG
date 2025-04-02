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

  int n = 0, cost = 0, m = 0;
  cin >> n;

  int ns[n];
  for(int i = 0; i < n; i++){
    int x;
    cin >> x;

    ns[i] = x;
  }

  map<int, int> repetitions;
  for(int i = 0; i < n; i++){
    repetitions[ns[i]]++;
  }
  m = max_element(repetitions.begin(), repetitions.end(), [](const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second; })->f;


  if(m == 1) {
    //average of ns
    int sum = 0;  
    for(int i = 0; i < n; i++){
      sum += ns[i];
    }
    double mean = double(sum)/double(n);
    m = round(mean);
  }

  for(int i = 0; i < n; i++){
    if(ns[i] > m+1) {
      cost += abs(ns[i] - (m+1));
    } else if(ns[i] < m-1) {
      cost += abs(ns[i] - (m-1));
    }
  }

  cout << m << " " << cost << endl;

	exit(0);
}
