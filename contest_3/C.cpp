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
	int storeAmount = 0;
	cin >> storeAmount;
	vector<int> stores(storeAmount);
	for(int i = 0; i < storeAmount; i++) {
		cin >> stores[i];
	}

	sort(stores.begin(), stores.end());

	int daysToBuy = 0;
	cin >> daysToBuy;
	for(int i = 0; i < daysToBuy; i++) {
		int pennyPerDay;
		cin >> pennyPerDay;

		int left = 0, right = storeAmount;
		int mid;
		int result = -1;
		while(left <= right) {
			mid = (left + right) / 2;
			if((stores[mid] < pennyPerDay) && (stores[mid+1] > pennyPerDay)) {
				result = mid + 1;
				break;
			}

			if(stores[mid] == pennyPerDay) {
				result = mid + 1;
				left = mid + 1;
			} else if(pennyPerDay < stores[mid]) {
				right = mid - 1;				
			} else {
				left = mid + 1;
			}
		}

		if(result != -1) {
			if(result > storeAmount) result = storeAmount;
			cout << result << endl;
		} else cout << 0 << endl;
	}
  
	exit(0);
}
