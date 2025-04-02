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
	string initial;
	char options[3] = {'R', 'G', 'B'};

	cin >> n;
	cin >> initial;

	int count = 0;
	for(int i = 0; i < n; i++) {
		if(initial[i] != initial[i+1]) continue;

		count++;
		for(int j = 0; j < 3; j++) {
			initial[i+1] = options[j];
			if((initial[i] != initial[i+1]) && (initial[i+1] != initial[i+2])) break;
		}
	}
	cout << count << endl;
	cout << initial << endl;
  
	exit(0);
}
