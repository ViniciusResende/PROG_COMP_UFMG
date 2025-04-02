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

	int divisorsAmount = 0;
	cin >> divisorsAmount;

	vector<int> divisors;


	for(int i = 0; i < divisorsAmount; i++) {
		int value;
		cin >> value;
		divisors.push_back(value);
	}

	sort(divisors.begin(), divisors.end());

	int max = divisors[divisorsAmount - 1];

	bool isPrime = false;
	for(int i = 2; i < max; i++) {
		if(max % i == 0) {
			isPrime = false;
			break;
		} else {
			isPrime = true;
		}
	}

	if(isPrime) {
		cout << max << " " << divisors[divisorsAmount - 2] << endl;
		exit(0);
	}

	for(int i = divisors.size() - 1; i >= 0; i--) {
		if(divisors[i] != divisors[i-1]) {
			if(max % divisors[i] == 0) divisors.erase(divisors.begin() + i);
		}
	}
  
	cout << max << " " << divisors[divisors.size() - 1] << endl;
	exit(0);
}
