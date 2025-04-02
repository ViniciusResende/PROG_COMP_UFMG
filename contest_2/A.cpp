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

  int queries = 0;
  cin >> queries;

  for(int i = 0; i < queries; i++){
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;

    if(l1 != l2){
      cout << l1 << " " << l2 << endl;
    } else if(l1 != r2){
      cout << l1 << " " << r2 << endl;
    } else if(r1 != l2){
      cout << r1 << " " << l2 << endl;
    } else if(r1 != r2){
      cout << r1 << " " << r2 << endl;
    }
  }
  
	exit(0);
}
