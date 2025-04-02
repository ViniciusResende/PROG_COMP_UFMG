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

/**
 * 3 -> 0: descanso, 1: contest, 2: acad
 * memo[i][3] = menor quantidade de descansos ate o iesimo dia


 * memo[i][0] = min(memo[i][0], memo[i][1], memo[i][2])
 * memo[i][1] = min(memo[i][0], memo[i][2])
 * memo[i][2] = min(memo[i][0], memo[i][1])

*/

vector<char> dayOptions;
vector<vector<int>> memo;

int minimum(int a, int b, int c) {
  return std::min(std::min(a, b), c);
}

int recursive(int i, int activity) {
	if(memo[i][activity] != INF) {
		return memo[i][activity];
	}

	char currDay = dayOptions[i];
	
	if(currDay == 0) {
		memo[i][activity] = minimum(recursive(i-1, 0), recursive(i-1, 1), recursive(i-1, 2));
	} else if(currDay == 1) {
		if(activity == 0) {
			memo[i][activity] = minimum(recursive(i-1, 0), recursive(i-1, 1), recursive(i-1, 2));
		} if(activity == 1) {
			memo[i][activity] = min(recursive(i-1, 0), recursive(i-1, 2));
		} if(activity == 2) {
			memo[i][activity] = INF - 1;
		}
	} else if(currDay == 2) {
		if(activity == 0) {
			memo[i][activity] = minimum(recursive(i-1, 0), recursive(i-1, 1), recursive(i-1, 2));
		} if(activity == 1) {
			memo[i][activity] = INF - 1;
		} if(activity == 2) {
			memo[i][activity] = min(recursive(i-1, 0), recursive(i-1, 1));
		}
	}	else if(currDay == 3) {
		if(activity == 0) {
			memo[i][activity] = minimum(recursive(i-1, 0), recursive(i-1, 1), recursive(i-1, 2));
		} if(activity == 1) {
			memo[i][activity] = min(recursive(i-1, 0), recursive(i-1, 2));
		} if(activity == 2) {
			memo[i][activity] = min(recursive(i-1, 0), recursive(i-1, 1));
		}
	}

	return memo[i][activity];
}

int main(){ _
	int vacationDays = 0;
	cin >> vacationDays;
	dayOptions = vector<char>(vacationDays);
	for(int i = 0; i < vacationDays; i++) {
		cin >> dayOptions[i];
	}

	memo = vector<vector<int>>(vacationDays, vector<int>(3, INF));

  cout << minimum(recursive(vacationDays-1, 0), recursive(vacationDays-1, 1), recursive(vacationDays-1, 2)) << endl;
	exit(0);
}
