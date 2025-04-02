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
 * 314 -> 431
 * 159 -> 951
 * _ _
*/

int main(){ _
  int testCases;  
  cin >> testCases;

  while(testCases) {
    int stringLen;
    cin >> stringLen;

    string RED, BLUE;
    cin >> RED >> BLUE;

    sort(RED.begin(), RED.end());
    sort(BLUE.begin(), BLUE.end());

    int redBigger = 0, blueBigger = 0;
    for(int i = 0; i < stringLen; i++) {
      if(RED[i] > BLUE[i]) redBigger++;
      else if(RED[i] < BLUE[i]) blueBigger++;
    }

    if(redBigger > blueBigger) {
      cout << "RED" << endl;
    } else if(redBigger < blueBigger) {
      cout << "BLUE" << endl;
    } else {
      cout << "EQUAL" << endl;
    }

    testCases--;
  }
	
  exit(0);
}
