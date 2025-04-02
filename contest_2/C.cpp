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

  vector<string> threeComb = {"RGB", "RBG", "BRG", "BGR", "GBR", "GRB"};
	vector<int> combCount = {0, 0, 0, 0, 0, 0};
	int n;
	string initial;

	cin >> n;
	cin >> initial;

	for(int i = 1; i < n; i++) {
		int charIndex = (i % 3) - 1;
		if(charIndex == -1) charIndex = 2;
		char currentChar = initial[i-1];

		for(int j = 0; j < threeComb.size(); j++) {
			if(currentChar != threeComb[j][charIndex]) {
				combCount[j]++;
			}
		}
	}

	int min = INF, minIndex = 0;

	for(int i = 0; i < combCount.size(); i++) {
		if(combCount[i] < min) {
			min = combCount[i];
			minIndex = i;
		}
	}

	cout << min << endl;
	for(int i = 0; i < n; i++) cout << threeComb[minIndex][i % 3]; // repeat the pattern until reaches n
	cout << endl;

	exit(0);
}
