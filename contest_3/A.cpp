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
  map<int, int> positions;
  int testCases = 0;
  cin >> testCases;
  while(testCases) {
    int robotsAmount = 0;
    int highestPos = -1;
    cin >> robotsAmount;
    for(int i = 0; i < robotsAmount; i++) {
      int currRobotPos = -1;
      cin >> currRobotPos;

      if(positions.find(currRobotPos) == positions.end()) positions[currRobotPos] = 1;
      else positions[currRobotPos]++;

      highestPos = max(highestPos, currRobotPos);
    }

    bool valid = true;
    int prevCount = INF;
    for (int i = 0; i <= highestPos; i++) {
      if(prevCount < positions[i]) {
        valid = false;
        break;
      }

      prevCount = positions[i];
    }

    cout << (valid ? "YES" : "NO") << endl;

    positions.clear();
    testCases--;
  }
  
  
	exit(0);
}
